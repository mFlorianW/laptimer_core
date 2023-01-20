#include "SqliteSessionDatabase.hpp"
#include "private/Statement.hpp"
#include <cstring>
#include <iostream>

using namespace LaptimerCore::Private::SqliteHelper;

namespace LaptimerCore::Session
{

SqliteSessionDatabase::SqliteSessionDatabase(const std::string &databaseFile)
    : mDbConnection{Connection::connection(databaseFile)}
{
    auto *rawHandle = mDbConnection.getRawHandle();
    sqlite3_update_hook(rawHandle, &SqliteSessionDatabase::handleUpdates, this);
    updateIndexMapper();
}

SqliteSessionDatabase::~SqliteSessionDatabase() = default;

std::size_t SqliteSessionDatabase::getSessionCount()
{
    return mIndexMapper.size();
}

std::optional<Common::SessionData> SqliteSessionDatabase::getSessionByIndex(std::size_t index) const noexcept
{
    // clang-format off
    constexpr auto sessionQuery = "SELECT "
                                    "Session.Date, Session.Time, Session.TrackId "
                                  "FROM "
                                    "Session "
                                  "WHERE "
                                    "Session.SessionId = ?";
    // clang-format on
    const auto sessionIndex = mIndexMapper.find(index);
    if (sessionIndex == mIndexMapper.cend())
    {
        return std::nullopt;
    }

    auto sessionStm = Statement{mDbConnection};
    if ((sessionStm.prepare(sessionQuery) != PrepareResult::Ok) ||
        (sessionStm.bindIntValue(1, static_cast<int>(sessionIndex->second)) != BindResult::Ok) ||
        (sessionStm.execute() != ExecuteResult::Row) || (sessionStm.getColumnCount() < 3))
    {
        std::cout << "Error query session:" << mDbConnection.getErrorMessage() << std::endl;
        return std::nullopt;
    }

    const auto trackId = static_cast<std::size_t>(sessionStm.getIntColumn(2).value_or(0));
    auto trackData = getTrack(trackId);
    if (!trackData.has_value())
    {
        return std::nullopt;
    }

    auto laps = getLapsOfSession(sessionIndex->second);
    if (!laps.has_value())
    {
        return std::nullopt;
    }

    auto session = Common::SessionData{trackData.value_or(Common::TrackData{}),
                                       Common::Date{sessionStm.getStringColumn(0).value_or("")},
                                       Common::Timestamp{sessionStm.getStringColumn(1).value_or("")}};
    session.addLaps(laps.value_or(std::vector<Common::LapData>{}));
    return session;
}

bool SqliteSessionDatabase::storeSession(const Common::SessionData &session)
{
    auto sessionId = getSessionId(session);
    if (sessionId.has_value())
    {
        return updateSession(sessionId.value_or(0), session);
    }
    return storeNewSession(session);
}

void SqliteSessionDatabase::deleteSession(std::size_t index)
{
    // clang-format off
    constexpr auto sessionDeleteQuery = "DELETE "
                                        "FROM "
                                            "Session "
                                        "WHERE "
                                            "Session.SessionId = ?";
    // clang-format on
    const auto sessionIndex = mIndexMapper.find(index);
    if (sessionIndex == mIndexMapper.cend())
    {
        std::cout << "Failed to delete session under index" << index << " not found." << std::endl;
        return;
    }

    auto sessionDeleteStm = Statement{mDbConnection};
    if ((sessionDeleteStm.prepare(sessionDeleteQuery) != PrepareResult::Ok) ||
        (sessionDeleteStm.bindIntValue(1, static_cast<int>(sessionIndex->second)) != BindResult::Ok) ||
        (sessionDeleteStm.execute() != ExecuteResult::Ok))
    {
        std::cout << "Failed to delete session under index" << index << "Error:" << mDbConnection.getErrorMessage()
                  << std::endl;
    }
    updateIndexMapper();
    sessionDeleted.emit(index);
}

bool SqliteSessionDatabase::updateSession(std::size_t sessionId, const Common::SessionData &session)
{
    // In the update case it's only necessary to add new laps to session if needed because other parts of a session
    // shouldn't be changed.
    const auto storedLaps = getLapsOfSession(sessionId);
    if (!storedLaps.has_value())
    {
        return false;
    }

    const auto sessionLaps = session.getLaps();
    if (sessionLaps.size() < storedLaps->size())
    {
        return true;
    }

    for (std::size_t lapIndex = storedLaps->size(); lapIndex < sessionLaps.size(); ++lapIndex)
    {
        if (!storeLapOfSession(sessionId, lapIndex, session.getLaps().at(lapIndex)))
        {
            return false;
        }
    }

    const auto updatedIndex = getIndexOfSessionId(sessionId);
    if (!updatedIndex.has_value())
    {
        return false;
    }
    sessionUpdated.emit(*updatedIndex);
    return true;
}

bool SqliteSessionDatabase::storeNewSession(const Common::SessionData &session)
{
    // clang-format off
    constexpr auto insertQuery = "INSERT INTO SESSION (TrackId, Date, Time) "
                                 "VALUES "
                                 "((SELECT TrackId FROM Track WHERE Track.Name = ?), ?, ?)";
    // clang-format on

    // insert the session
    auto insertStm = Statement{mDbConnection};
    if ((insertStm.prepare(insertQuery) != PrepareResult::Ok) ||
        (insertStm.bindStringValue(1, session.getTrack().getTrackName()) != BindResult::Ok) ||
        (insertStm.bindStringValue(2, session.getSessionDate().asString()) != BindResult::Ok) ||
        (insertStm.bindStringValue(3, session.getSessionTime().asString()) != BindResult::Ok) ||
        (insertStm.execute() != ExecuteResult::Ok))
    {
        std::cout << "Error insert session:" << mDbConnection.getErrorMessage() << std::endl;
        return false;
    }

    // get the session for inserting the laps.
    auto sessionId = getSessionId(session);
    if (!sessionId.has_value())
    {
        std::cout << "Failed to query session of new stored session." << std::endl;
        return false;
    }

    // insert the laps of the session
    const auto laps = session.getLaps();
    for (std::size_t lapIndex = 0; lapIndex < laps.size(); ++lapIndex)
    {
        if (!storeLapOfSession(*sessionId, lapIndex, laps.at(lapIndex)))
        {
            return false;
        }
    }

    updateIndexMapper();
    const auto addedIndex = getSessionCount() > 0 ? getSessionCount() - 1 : 0;
    sessionAdded.emit(addedIndex);
    return true;
}

std::optional<std::size_t> SqliteSessionDatabase::getSessionIdOfIndex(std::size_t sessionIndex) const noexcept
{
    const auto sessionIds = getSessionIds();
    if (sessionIndex > sessionIds.size())
    {
        return std::nullopt;
    }

    return sessionIds[sessionIndex];
}

std::optional<std::size_t> SqliteSessionDatabase::getSessionId(const Common::SessionData &session) const noexcept
{
    // clang-format off
    constexpr auto sessionIdQuery = "SELECT "
                                        "Session.SessionId "
                                    "FROM "
                                        "Session "
                                    "WHERE "
                                        "Session.date = ? AND Session.time = ?";
    // clang-format on
    auto sessionIdStm = Statement{mDbConnection};
    if ((sessionIdStm.prepare(sessionIdQuery) != PrepareResult::Ok) ||
        (sessionIdStm.bindStringValue(1, session.getSessionDate().asString()) != BindResult::Ok) ||
        (sessionIdStm.bindStringValue(2, session.getSessionTime().asString()) != BindResult::Ok))
    {
        std::cout << "Error query session id:" << mDbConnection.getErrorMessage() << std::endl;
        return std::nullopt;
    }

    if ((sessionIdStm.execute() == ExecuteResult::Row) && (sessionIdStm.getIntColumn(0).has_value()))
    {
        return static_cast<std::size_t>(sessionIdStm.getIntColumn(0).value());
    }
    return std::nullopt;
}

std::optional<std::size_t> SqliteSessionDatabase::getIndexOfSessionId(std::size_t sessionId) const noexcept
{
    const auto sessionIds = getSessionIds();
    auto idIter =
        std::find_if(sessionIds.cbegin(), sessionIds.cend(), [sessionId](std::size_t id) { return id == sessionId; });
    if (idIter != sessionIds.cend())
    {
        return std::distance(sessionIds.cbegin(), idIter);
    }
    return std::nullopt;
}

std::vector<std::size_t> SqliteSessionDatabase::getSessionIds() const noexcept
{
    // clang-format off
    constexpr auto sessionIdsQuery = "SELECT "
                                        "Session.SessionId "
                                    "FROM "
                                        "Session";
    // clang-format on
    auto sessionIdsStm = Statement{mDbConnection};
    if (sessionIdsStm.prepare(sessionIdsQuery) != PrepareResult::Ok)
    {
        std::cout << "Failed to prepare query for session ids. Error: " << mDbConnection.getErrorMessage() << std::endl;
        return {};
    }

    auto sessionIds = std::vector<std::size_t>();
    auto rowReadResult = ExecuteResult::Error;
    while (((rowReadResult = sessionIdsStm.execute()) == ExecuteResult::Row) && (sessionIdsStm.getColumnCount() > 0))
    {
        const auto sessionIndex = sessionIdsStm.getIntColumn(0);
        if (sessionIndex.has_value())
        {
            sessionIds.push_back(*sessionIndex);
        }
        else
        {
            return {};
        }
    }

    return sessionIds;
}

std::optional<std::vector<Common::LapData>> SqliteSessionDatabase::getLapsOfSession(
    std::size_t sessionId) const noexcept
{
    // clang-format off
    constexpr auto lapIdQuery = "SELECT "
                                    "Lap.LapId "
                                "FROM "
                                    "Lap "
                                "WHERE "
                                    "Lap.SessionId = ?";
    constexpr auto sektorQuery = "SELECT "
                                    "SektorTime.Time "
                                 "FROM "
                                    "Session "
                                 "LEFT JOIN LAP ON "
                                    "Session.SessionId = Lap.SessionId "
                                 "LEFT JOIN SektorTime ON "
                                    "SektorTime.LapId = Lap.LapId "
                                 "WHERE "
                                     "Session.SessionId = ? AND SektorTime.LapId = ? ORDER BY SektorTime.SektorIndex AND Lap.LapIndex ASC";
    // clang-format on
    auto lapIds = std::vector<std::size_t>{};
    auto lapIdStm = Statement{mDbConnection};
    if ((lapIdStm.prepare(lapIdQuery) != PrepareResult::Ok) ||
        (lapIdStm.bindIntValue(1, static_cast<int>(sessionId)) != BindResult::Ok))
    {
        std::cout << "Error prepare query lap ids:" << mDbConnection.getErrorMessage() << std::endl;
        return std::nullopt;
    }

    auto state = ExecuteResult::Error;
    while (((state = lapIdStm.execute()) == ExecuteResult::Row) && (lapIdStm.getColumnCount() > 0))
    {
        auto lapId = lapIdStm.getIntColumn(0);
        if (lapId.has_value())
        {
            lapIds.emplace_back(lapId.value_or(0));
        }
    }

    if (state != ExecuteResult::Ok)
    {
        std::cout << "Error query lap ids:" << mDbConnection.getErrorMessage() << std::endl;
        return std::nullopt;
    }

    auto laps = std::vector<Common::LapData>{};
    for (const auto &lapId : lapIds)
    {
        auto lapData = Common::LapData{};
        auto sektorStm = Statement{mDbConnection};
        if ((sektorStm.prepare(sektorQuery) != PrepareResult::Ok) ||
            (sektorStm.bindIntValue(1, static_cast<int>(sessionId)) != BindResult::Ok) ||
            (sektorStm.bindIntValue(2, static_cast<int>(lapId)) != BindResult::Ok))
        {
            std::cout << "Error prepare lap query:" << mDbConnection.getErrorMessage() << std::endl;
            return std::nullopt;
        }

        while (((state = sektorStm.execute()) == ExecuteResult::Row) && (sektorStm.getColumnCount() > 0))
        {
            const auto sektorTime = sektorStm.getStringColumn(0);
            if (sektorTime.has_value())
            {
                lapData.addSectorTime(Common::Timestamp{sektorTime.value_or("")});
            }
        }

        if (state != ExecuteResult::Ok)
        {
            std::cout << "Error query lap ids:" << mDbConnection.getErrorMessage() << std::endl;
            return std::nullopt;
        }
        laps.push_back(lapData);
    }

    return laps;
}

std::optional<Common::TrackData> SqliteSessionDatabase::getTrack(std::size_t trackId) const noexcept
{
    // clang-format off
    constexpr auto trackQuery =
        "SELECT TrackId, Track.Name, FL.Latitude AS FlLat, FL.Longitude AS FlLong, "
        "SL.Latitude AS SlLat, SL.Longitude AS SlLong from Track LEFT JOIN Position FL ON Track.Finishline = "
        "FL.PositionId LEFT JOIN Position SL ON Track.Startline = SL.PositionId WHERE Track.TrackId = ?";

    constexpr auto sektorQuery =
        "SELECT PO.Latitude, PO.Longitude FROM Track JOIN Sektor SE ON Track.TrackId = SE.TrackId JOIN "
        "Position PO ON SE.PositionId = PO.PositionId WHERE Track.TrackId = ? ORDER BY SE.SektorIndex ASC";
    // clang-format on
    Statement stm{mDbConnection};
    if ((stm.prepare(trackQuery) != PrepareResult::Ok) ||
        (stm.bindIntValue(1, static_cast<int>(trackId)) != BindResult::Ok) || (stm.execute() != ExecuteResult::Row))
    {
        std::cout << "Error prepare track statement for id:" << trackId << "Error:" << mDbConnection.getErrorMessage();
        return std::nullopt;
    }
    auto track = LaptimerCore::Common::TrackData{};
    track.setTrackName(stm.getStringColumn(1).value_or(""));
    track.setFinishline({stm.getFloatColumn(2).value_or(0), stm.getFloatColumn(3).value_or(0)});
    if (stm.hasColumnValue(4) == HasColumnValueResult::Ok && stm.hasColumnValue(5) == HasColumnValueResult::Ok)
    {
        track.setStartline({stm.getFloatColumn(4).value_or(0), stm.getFloatColumn(5).value_or(0)});
    }

    // Request sektor
    Statement sektorStm{mDbConnection};
    if (sektorStm.prepare(sektorQuery) != PrepareResult::Ok ||
        sektorStm.bindIntValue(1, static_cast<int>(trackId)) != BindResult::Ok)
    {
        return std::nullopt;
    }

    auto sections = std::vector<LaptimerCore::Common::PositionData>{};
    while (sektorStm.execute() == ExecuteResult::Row && sektorStm.getColumnCount() == 2)
    {
        sections.emplace_back(sektorStm.getFloatColumn(0).value_or(0), sektorStm.getFloatColumn(1).value_or(0));
    }
    track.setSections(sections);
    return track;
}

bool SqliteSessionDatabase::storeLapOfSession(std::size_t sessionId,
                                              std::size_t lapIndex,
                                              const Common::LapData &lapData) const noexcept
{
    // clang-format off
    constexpr auto insertLapQuery = "INSERT INTO Lap(SessionId, LapIndex) "
                                    "VALUES "
                                    "(?, ?)";
    constexpr auto lapIdQuery = "SELECT Lap.LapId FROM Lap WHERE Lap.SessionId = ? AND Lap.LapIndex = ?";
    constexpr auto insetSektorQuery = "INSERT INTO SektorTime(LapId, Time, SektorIndex) "
                                      "VALUES "
                                      "(?, ?, ?)";
    // clang-format on
    auto lapInsertStm = Statement{mDbConnection};
    if ((lapInsertStm.prepare(insertLapQuery) != PrepareResult::Ok) ||
        (lapInsertStm.bindIntValue(1, static_cast<int>(sessionId)) != BindResult::Ok) ||
        (lapInsertStm.bindIntValue(2, static_cast<int>(lapIndex)) != BindResult::Ok) ||
        (lapInsertStm.execute() != ExecuteResult::Ok))
    {
        std::cout << "Error query session id:" << mDbConnection.getErrorMessage() << std::endl;
        return false;
    }

    auto lapIdStm = Statement{mDbConnection};
    if ((lapIdStm.prepare(lapIdQuery) != PrepareResult::Ok) ||
        (lapIdStm.bindIntValue(1, static_cast<int>(sessionId)) != BindResult::Ok) ||
        (lapIdStm.bindIntValue(2, static_cast<int>(lapIndex)) != BindResult::Ok) ||
        (lapIdStm.execute() != ExecuteResult::Row) || (!lapIdStm.getIntColumn(0).has_value()))
    {
        std::cout << "Error failed to query lap id:" << mDbConnection.getErrorMessage() << std::endl;
        return false;
    }
    const auto lapId = *lapIdStm.getIntColumn(0);
    auto insertSektorStm = Statement{mDbConnection};
    for (std::size_t sektorTimeIndex = 0; sektorTimeIndex < lapData.getSectorTimeCount(); ++sektorTimeIndex)
    {
        if ((insertSektorStm.prepare(insetSektorQuery) != PrepareResult::Ok) ||
            (insertSektorStm.bindIntValue(1, lapId) != BindResult::Ok) ||
            (insertSektorStm.bindStringValue(2, lapData.getSectorTime(sektorTimeIndex)->asString()) !=
             BindResult::Ok) ||
            (insertSektorStm.bindIntValue(3, static_cast<int>(sektorTimeIndex)) != BindResult::Ok) ||
            (insertSektorStm.execute() != ExecuteResult::Ok))
        {
            std::cout << "Error failed to insert sektor:" << mDbConnection.getErrorMessage() << std::endl;
            return false;
        }
    }
    return true;
}

void SqliteSessionDatabase::handleUpdates(void *objPtr,
                                          int event,
                                          char const *database,
                                          char const *table,
                                          sqlite3_int64 rowId)
{
    constexpr auto sessionTable = "Session";
    if ((event == SQLITE_DELETE) && (std::strcmp(table, sessionTable) == 0))
    {
        auto sessionDatabase = static_cast<SqliteSessionDatabase *>(objPtr);
        for (const auto &[index, sessionId] : sessionDatabase->mIndexMapper)
        {
            if (sessionId == static_cast<std::size_t>(rowId))
            {
                sessionDatabase->sessionDeleted.emit(index);
                sessionDatabase->mIndexMapper.erase(index);
                break;
            }
        }
    }
}

void SqliteSessionDatabase::updateIndexMapper()
{
    // clang-format off
    constexpr auto sessionIdsQuery = "SELECT "
                                          "Session.SessionId "
                                      "FROM "
                                          "Session "
                                      "ORDER BY "
                                          "Session.SessionId  "
                                      "ASC";
    // clang-format on
    auto sessionIdsStm = Statement{mDbConnection};
    if (sessionIdsStm.prepare(sessionIdsQuery) != PrepareResult::Ok)
    {
        std::cout << "Failed to query session count. Error:" << mDbConnection.getErrorMessage() << std::endl;
        return;
    }

    mIndexMapper.clear();
    auto executeResult = ExecuteResult::Error;
    auto index = std::size_t{0};
    while (((executeResult = sessionIdsStm.execute()) == ExecuteResult::Row) && (sessionIdsStm.getColumnCount() == 1))
    {
        const auto sessionId = sessionIdsStm.getIntColumn(0);
        if (sessionId.has_value())
        {
            mIndexMapper.emplace(index, *sessionId);
            ++index;
        }
    }

    if (executeResult != ExecuteResult::Ok)
    {
        mIndexMapper.clear();
        std::cout << "Failed to query all session ids. Error:" << mDbConnection.getErrorMessage() << std::endl;
    }
}

} // namespace LaptimerCore::Session

#include "SqliteSessionDatabase.hpp"
#include <Statement.hpp>
#include <iostream>

using namespace LaptimerCore::Private::SqliteHelper;

namespace LaptimerCore::Session
{

SqliteSessionDatabase::SqliteSessionDatabase(const std::string &databaseFile)
{
    mDbConnection.open(databaseFile);
}

SqliteSessionDatabase::~SqliteSessionDatabase() = default;

std::size_t SqliteSessionDatabase::getSessionCount()
{
    return 0;
}

std::optional<Common::SessionData> SqliteSessionDatabase::getSessionByIndex(std::size_t index) const noexcept
{
    // clang-format off
    constexpr auto sessionQuery = "SELECT "
                                    "Session.SessionId, Session.Date, Session.Time, Session.TrackId "
                                  "FROM "
                                    "Session "
                                  "LEFT JOIN Track ON "
                                    "Track.TrackId = Session.TrackId";
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
    auto sessionStm = Statement{mDbConnection};
    if ((sessionStm.prepare(sessionQuery) != PrepareResult::Ok) || (sessionStm.execute() != ExecuteResult::Row) ||
        (sessionStm.getColumnCount() < 4))
    {
        std::cout << "Error query session:" << mDbConnection.getErrorMessage() << std::endl;
        return std::nullopt;
    }

    const auto sessionId = static_cast<std::size_t>(sessionStm.getIntColumn(0).value_or(0));
    const auto trackId = static_cast<std::size_t>(sessionStm.getIntColumn(3).value_or(0));
    auto trackData = getTrack(trackId);
    if (!trackData.has_value())
    {
        return std::nullopt;
    }
    auto session = Common::SessionData{trackData.value_or(Common::TrackData{}),
                                       Common::Date{sessionStm.getStringColumn(1).value_or("")},
                                       Common::Timestamp{sessionStm.getStringColumn(2).value_or("")}};

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
        session.addLap(lapData);
    }

    return session;
}

bool SqliteSessionDatabase::storeSession(const Common::SessionData &session)
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
    // clang-format off
    constexpr auto sessionIdQuery = "SELECT Session.SessionId FROM Session WHERE Session.date = ? AND Session.time = ?";
    // clang-format on
    auto sessionIdStm = Statement{mDbConnection};
    if ((sessionIdStm.prepare(sessionIdQuery) != PrepareResult::Ok) ||
        (sessionIdStm.bindStringValue(1, session.getSessionDate().asString()) != BindResult::Ok) ||
        (sessionIdStm.bindStringValue(2, session.getSessionTime().asString()) != BindResult::Ok) ||
        (sessionIdStm.execute() != ExecuteResult::Row) || (!sessionIdStm.getIntColumn(0).has_value()))
    {
        std::cout << "Error query session id:" << mDbConnection.getErrorMessage() << std::endl;
        return false;
    }
    auto sessionId = static_cast<std::size_t>(sessionIdStm.getIntColumn(0).value());

    // insert the laps of the session
    // clang-format off
    constexpr auto insertLapQuery = "INSERT INTO Lap(SessionId, LapIndex) "
                                    "VALUES "
                                    "(?, ?)";
    constexpr auto lapIdQuery = "SELECT Lap.LapId FROM Lap WHERE Lap.SessionId = ? AND Lap.LapIndex = ?";
    constexpr auto insetSektorQuery = "INSERT INTO SektorTime(LapId, Time, SektorIndex) "
                                      "VALUES "
                                      "(?, ?, ?)";
    // clang-format on
    for (std::size_t i = 0; i < session.getNumberOfLaps(); ++i)
    {
        auto lapInsertStm = Statement{mDbConnection};
        if ((lapInsertStm.prepare(insertLapQuery) != PrepareResult::Ok) ||
            (lapInsertStm.bindIntValue(1, static_cast<int>(sessionId)) != BindResult::Ok) ||
            (lapInsertStm.bindIntValue(2, static_cast<int>(i)) != BindResult::Ok) ||
            (lapInsertStm.execute() != ExecuteResult::Ok))
        {
            std::cout << "Error query session id:" << mDbConnection.getErrorMessage() << std::endl;
            return false;
        }

        auto lapIdStm = Statement{mDbConnection};
        if ((lapIdStm.prepare(lapIdQuery) != PrepareResult::Ok) ||
            (lapIdStm.bindIntValue(1, static_cast<int>(sessionId)) != BindResult::Ok) ||
            (lapIdStm.bindIntValue(2, static_cast<int>(i)) != BindResult::Ok) ||
            (lapIdStm.execute() != ExecuteResult::Row) || (!lapIdStm.getIntColumn(0).has_value()))
        {
            std::cout << "Error failed to query lap id:" << mDbConnection.getErrorMessage() << std::endl;
            return false;
        }
        auto lapId = lapIdStm.getIntColumn(0).value();

        auto insertSektorStm = Statement{mDbConnection};
        for (std::size_t sektorTimeIndex = 0; sektorTimeIndex < session.getLap(i)->getSectorTimeCount();
             ++sektorTimeIndex)
        {
            const auto lapData = session.getLap(i);
            if ((insertSektorStm.prepare(insetSektorQuery) != PrepareResult::Ok) ||
                (insertSektorStm.bindIntValue(1, lapId) != BindResult::Ok) ||
                (insertSektorStm.bindStringValue(2, lapData->getSectorTime(sektorTimeIndex)->asString()) !=
                 BindResult::Ok) ||
                (insertSektorStm.bindIntValue(3, static_cast<int>(sektorTimeIndex)) != BindResult::Ok) ||
                (insertSektorStm.execute() != ExecuteResult::Ok))
            {
                std::cout << "Error failed to insert sektor:" << mDbConnection.getErrorMessage() << std::endl;
                return false;
            }
        }
    }

    sessionAdded.emit(0);
    return true;
}

void SqliteSessionDatabase::deleteSession(std::size_t index)
{
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
        sections.emplace_back(
            Common::PositionData{sektorStm.getFloatColumn(0).value_or(0), sektorStm.getFloatColumn(1).value_or(0)});
    }
    track.setSections(sections);
    return track;
}

} // namespace LaptimerCore::Session

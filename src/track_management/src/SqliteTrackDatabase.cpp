#include "SqliteTrackDatabase.hpp"
#include <Statement.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace LaptimerCore::Private::SqliteHelper;

namespace LaptimerCore::TrackManagement
{

SqliteTrackDatabase::SqliteTrackDatabase(const std::string &pathToDatabase)
{
    // TODO log error when fails.
    mDbConnection.open(pathToDatabase);
}

SqliteTrackDatabase::~SqliteTrackDatabase() = default;

std::size_t SqliteTrackDatabase::getTrackCount()
{
    constexpr auto statementStr = "SELECT COUNT(TrackId) FROM Track";
    Statement stm{mDbConnection};
    if (stm.prepare(statementStr) != PrepareResult::Ok || stm.execute() != ExecuteResult::Row ||
        stm.getColumnCount() == 0)
    {
        std::cout << "Database Error: " << mDbConnection.getErrorMessage() << "\n";
        return 0;
    }

    return stm.getIntColumn(0).value_or(0);
}

std::vector<Common::TrackData> SqliteTrackDatabase::getTracks()
{
    constexpr auto trackQuery =
        "SELECT TrackId, Track.Name, FL.Latitude AS FlLat, FL.Longitude AS FlLong, "
        "SL.Latitude AS SlLat, SL.Longitude AS SlLong from Track LEFT JOIN Position FL ON Track.Finishline = "
        "FL.PositionId LEFT JOIN Position SL ON Track.Startline = SL.PositionId";
    auto tracksResult = std::vector<Common::TrackData>{};

    //    auto *stm = static_cast<sqlite3_stmt *>(nullptr);
    Statement stm{mDbConnection};
    if (stm.prepare(trackQuery) == PrepareResult::Ok)
    {
        while (stm.execute() == ExecuteResult::Row && stm.getColumnCount() == 6)
        {
            auto track = LaptimerCore::Common::TrackData{};
            auto trackId = stm.getIntColumn(0).value_or(0);
            track.setTrackName(stm.getStringColumn(1).value_or(""));
            track.setFinishline({stm.getFloatColumn(2).value_or(0), stm.getFloatColumn(3).value_or(0)});
            if (stm.hasColumnValue(4) == HasColumnValueResult::Ok && stm.hasColumnValue(5) == HasColumnValueResult::Ok)
            {
                track.setStartline({stm.getFloatColumn(4).value_or(0), stm.getFloatColumn(5).value_or(0)});
            }

            // Request sektor
            constexpr auto sektorQuery =
                "SELECT PO.Latitude, PO.Longitude FROM Track JOIN Sektor SE ON Track.TrackId = SE.TrackId JOIN "
                "Position PO ON SE.PositionId = PO.PositionId WHERE Track.TrackId = ? ORDER BY SE.SektorIndex ASC";
            Statement sektorStm{mDbConnection};
            if (sektorStm.prepare(sektorQuery) != PrepareResult::Ok ||
                sektorStm.bindIntValue(1, trackId) != BindResult::Ok)
            {
                tracksResult.clear();
                break;
            }

            auto sections = std::vector<LaptimerCore::Common::PositionData>{};
            while (sektorStm.execute() == ExecuteResult::Row && sektorStm.getColumnCount() == 2)
            {
                sections.emplace_back(Common::PositionData{sektorStm.getFloatColumn(0).value_or(0),
                                                           sektorStm.getFloatColumn(1).value_or(0)});
            }
            track.setSections(sections);
            tracksResult.emplace_back(track);
        }
    }
    return tracksResult;
}

bool SqliteTrackDatabase::saveTrack(const std::vector<Common::TrackData> &tracks)
{
    return false;
}

bool SqliteTrackDatabase::deleteTrack(const Common::TrackData &tracks)
{
    return false;
}

bool SqliteTrackDatabase::deleteAllTracks()
{
    return false;
}

} // namespace LaptimerCore::TrackManagement

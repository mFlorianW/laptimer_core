// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SqliteTrackDatabase.hpp"
#include "private/Statement.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace Rapid::Storage::Private;

namespace Rapid::Storage
{

SqliteTrackDatabase::SqliteTrackDatabase(std::string const& pathToDatabase)
    : mDbConnection{Connection::connection(pathToDatabase)}
{
}

SqliteTrackDatabase::~SqliteTrackDatabase() = default;

std::size_t SqliteTrackDatabase::getTrackCount()
{
    constexpr auto statementStr = "SELECT COUNT(TrackId) FROM Track";
    Statement stm{mDbConnection};
    if (stm.prepare(statementStr) != PrepareResult::Ok || stm.execute() != ExecuteResult::Row ||
        stm.getColumnCount() == 0) {
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

    Statement stm{mDbConnection};
    if (stm.prepare(trackQuery) == PrepareResult::Ok) {
        while (stm.execute() == ExecuteResult::Row && stm.getColumnCount() == 6) {
            auto track = Rapid::Common::TrackData{};
            auto trackId = stm.getIntColumn(0).value_or(0);
            track.setTrackName(stm.getStringColumn(1).value_or(""));
            track.setFinishline({stm.getFloatColumn(2).value_or(0), stm.getFloatColumn(3).value_or(0)});
            if (stm.hasColumnValue(4) == HasColumnValueResult::Ok &&
                stm.hasColumnValue(5) == HasColumnValueResult::Ok) {
                track.setStartline({stm.getFloatColumn(4).value_or(0), stm.getFloatColumn(5).value_or(0)});
            }

            // Request sektor
            constexpr auto sektorQuery =
                "SELECT PO.Latitude, PO.Longitude FROM Track JOIN Sektor SE ON Track.TrackId = SE.TrackId JOIN "
                "Position PO ON SE.PositionId = PO.PositionId WHERE Track.TrackId = ? ORDER BY SE.SektorIndex ASC";
            Statement sektorStm{mDbConnection};
            if (sektorStm.prepare(sektorQuery) != PrepareResult::Ok ||
                sektorStm.bindIntValue(1, trackId) != BindResult::Ok) {
                tracksResult.clear();
                break;
            }

            auto sections = std::vector<Rapid::Common::PositionData>{};
            while (sektorStm.execute() == ExecuteResult::Row && sektorStm.getColumnCount() == 2) {
                sections.emplace_back(Common::PositionData{sektorStm.getFloatColumn(0).value_or(0),
                                                           sektorStm.getFloatColumn(1).value_or(0)});
            }
            track.setSections(sections);
            tracksResult.emplace_back(track);
        }
    }
    return tracksResult;
}

bool SqliteTrackDatabase::saveTrack(std::vector<Common::TrackData> const& tracks)
{
    return false;
}

bool SqliteTrackDatabase::deleteTrack(std::size_t trackIndex)
{
    // clang-format off
    constexpr auto deleteTrackQuery = "DELETE "
                                     "FROM "
                                        "TRACK "
                                     "WHERE "
                                        "Track.TrackId = ?";
    // clang-format on
    auto const trackId = getTrackIdOfIndex(trackIndex);
    if (!trackId.has_value()) {
        std::cout << "Failed to delete Track. Index not found:" << trackIndex << std::endl;
        return false;
    }

    auto deleteTrackStm = Statement{mDbConnection};
    if ((deleteTrackStm.prepare(deleteTrackQuery) != PrepareResult::Ok) ||
        (deleteTrackStm.bindIntValue(1, static_cast<int>(*trackId)) != BindResult::Ok) ||
        (deleteTrackStm.execute() != ExecuteResult::Ok)) {
        std::cout << "Failed to delete track. Error:" << mDbConnection.getErrorMessage() << std::endl;
        return false;
    }
    return true;
}

bool SqliteTrackDatabase::deleteAllTracks()
{
    return false;
}

std::vector<std::size_t> SqliteTrackDatabase::getTrackIds() const noexcept
{
    // clang-format off
    constexpr auto trackIdQuery = "SELECT "
                                    "Track.TrackId "
                                  "FROM "
                                    "Track";
    // clang-format on
    auto trackIdStm = Statement{mDbConnection};
    if (trackIdStm.prepare(trackIdQuery) != PrepareResult::Ok) {
        std::cout << "Failed to prepare track id query. Error:" << mDbConnection.getErrorMessage();
        return {};
    }

    auto executeResult = ExecuteResult::Error;
    auto trackIds = std::vector<std::size_t>{};
    while (((executeResult = trackIdStm.execute()) == ExecuteResult::Row) && (trackIdStm.getColumnCount() > 0)) {
        auto const trackId = trackIdStm.getIntColumn(0);
        if (trackId.has_value()) {
            trackIds.push_back(*trackId);
        } else {
            return {};
        }
    }

    return trackIds;
}

std::optional<std::size_t> SqliteTrackDatabase::getTrackIdOfIndex(std::size_t trackIndex) const noexcept
{
    auto const trackIds = getTrackIds();
    if (trackIndex > trackIds.size()) {
        return std::nullopt;
    }

    return trackIds[trackIndex];
}

} // namespace Rapid::Storage

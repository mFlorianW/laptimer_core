// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SQLLITETRACKDATABASE_HPP
#define SQLLITETRACKDATABASE_HPP

#include "ITrackDatabase.hpp"
#include "private/Connection.hpp"
#include <optional>

namespace LaptimerCore::Storage
{
class SqliteTrackDatabase : public ITrackDatabase
{
public:
    /**
     * Creates an Instance of the SqliteTrackDatabase
     * @param pathToDatabase The path to the Sqlite database file
     */
    SqliteTrackDatabase(std::string const& pathToDatabase);

    /**
     * Destructor
     */
    ~SqliteTrackDatabase() override;

    /**
     * Deleted copy constructor
     */
    SqliteTrackDatabase(SqliteTrackDatabase const& other) = delete;

    /**
     * Deleted copy assignment
     */
    SqliteTrackDatabase& operator=(SqliteTrackDatabase const& other) = delete;

    /**
     * Deleted move constructor
     */
    SqliteTrackDatabase(SqliteTrackDatabase&& other) = delete;

    /**
     * Deleted move assignment
     */
    SqliteTrackDatabase& operator=(SqliteTrackDatabase&& other) = delete;

    /**
     * @copydoc ITrackdatabase::getTrackCount()
     */
    std::size_t getTrackCount() override;

    /**
     * @copydoc ITrackdatabase::loadTracks()
     */
    std::vector<Common::TrackData> getTracks() override;

    /**
     * @copydoc ITrackdatabase::saveTrack(const std::vector<Common::TrackData> &tracks)
     */
    bool saveTrack(std::vector<Common::TrackData> const& tracks) override;

    /**
     * @copydoc ITrackdatabase::deleteTrack(std::size_t trackIndex)
     */
    bool deleteTrack(std::size_t trackIndex) override;

    /**
     * @copydoc ITrackdatabase::deleteAllTracks()
     */
    bool deleteAllTracks() override;

private:
    std::vector<std::size_t> getTrackIds() const noexcept;
    std::optional<std::size_t> getTrackIdOfIndex(std::size_t trackIndex) const noexcept;

    Private::Connection& mDbConnection;
};

} // namespace LaptimerCore::Storage

#endif // SQLLITETRACKDATABASE_HPP

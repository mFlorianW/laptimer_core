#ifndef SQLLITETRACKDATABASE_HPP
#define SQLLITETRACKDATABASE_HPP

#include "ITrackDatabase.hpp"
#include <Connection.hpp>

namespace LaptimerCore::TrackManagement
{
class SqliteTrackDatabase : public ITrackDatabase
{
public:
    /**
     * Creates an Instance of the SqliteTrackDatabase
     * @param pathToDatabase The path to the Sqlite database file
     */
    SqliteTrackDatabase(const std::string &pathToDatabase);

    /**
     * Destructor
     */
    ~SqliteTrackDatabase() override;

    /**
     * Deleted copy constructor
     */
    SqliteTrackDatabase(const SqliteTrackDatabase &other) = delete;

    /**
     * Deleted copy assignment
     */
    SqliteTrackDatabase &operator=(const SqliteTrackDatabase &other) = delete;

    /**
     * Deleted move constructor
     */
    SqliteTrackDatabase(SqliteTrackDatabase &&other) = delete;

    /**
     * Deleted move assignment
     */
    SqliteTrackDatabase &operator=(SqliteTrackDatabase &&other) = delete;

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
    bool saveTrack(const std::vector<Common::TrackData> &tracks) override;

    /**
     * @copydoc ITrackdatabase::deleteTrack(const Common::TrackData &tracks)
     */
    bool deleteTrack(const Common::TrackData &tracks) override;

    /**
     * @copydoc ITrackdatabase::deleteAllTracks()
     */
    bool deleteAllTracks() override;

private:
    LaptimerCore::Private::SqliteHelper::Connection mDbConnection{};
};

} // namespace LaptimerCore::TrackManagement

#endif // SQLLITETRACKDATABASE_HPP

#ifndef SQLITESESSIONDATABASE_HPP
#define SQLITESESSIONDATABASE_HPP

#include "ISessionDatabase.hpp"
#include <Connection.hpp>

namespace LaptimerCore::Session
{

class SqliteSessionDatabase : public ISessionDatabase
{
public:
    /**
     * Constructs a SqliteSessionDatabase
     * @param databaseFile the path to the SQLITE database.
     */
    explicit SqliteSessionDatabase(const std::string &databaseFile);

    /**
     * Destructor
     */
    ~SqliteSessionDatabase() override;

    /**
     * Deleted copy constructor
     */
    SqliteSessionDatabase(const SqliteSessionDatabase &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    SqliteSessionDatabase &operator=(const SqliteSessionDatabase &other) = delete;

    /**
     * Deleted move constructor
     */
    SqliteSessionDatabase(SqliteSessionDatabase &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    SqliteSessionDatabase &operator=(SqliteSessionDatabase &&other) = delete;

    /**
     * @copydoc ISessionDatabase::getSessionCount()
     */
    std::size_t getSessionCount() override;

    /**
     * @copydoc ISessionDatabase::getSessionByIndex(std::size_t index)
     */
    std::optional<Common::SessionData> getSessionByIndex(std::size_t index) const noexcept override;

    /**
     * @copydoc ISessionDatabase::storeSession(Common::SessionData &session)
     */
    bool storeSession(const Common::SessionData &session) override;

    /**
     * @copydoc ISessionDatabase::deleteSession(std::size_t index)
     */
    void deleteSession(std::size_t index) override;

private:
    std::optional<Common::TrackData> getTrack(std::size_t trackId) const noexcept;

    Private::SqliteHelper::Connection mDbConnection{};
};

} // namespace LaptimerCore::Session
#endif // SQLITESESSIONDATABASE_HPP
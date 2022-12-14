#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <sqlite3.h>
#include <string>

namespace LaptimerCore::Private::SqliteHelper
{
/**
 * Return codes for opening the database.
 */
enum class OpenResult
{
    Ok,
    Error
};

/**
 * This Sqlite database connection. A connection is unique and is not copyable nor movable.
 */
class Connection final
{
public:
    /**
     * Creates an Connection instance
     */
    Connection() = default;

    /**
     * Default empty constructor
     */
    ~Connection();

    /**
     * Deleted copy constructor
     */
    Connection(const Connection &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    Connection &operator=(const Connection &other) = delete;

    /**
     * Deleted move constructor
     */
    Connection(Connection &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    Connection &operator=(Connection &&other) = delete;

    /**
     * Tries to open the sqlite3 database for the given string.
     * @param database The path to the database.
     * @return On success returns OpenResult::Successful otherwise
     */
    OpenResult open(const std::string &database);

    /**
     * Gives the last reported error message of the database. The function should be called when an operation of the
     * database failed. The error message is only after calling  @ref open() with OpenResult::Successful.
     * @return The error message of the database as string.
     */
    std::string getErrorMessage();

private:
    friend class Statement;
    /**
     * Gives the raw handle to the database. It's only valid after calling @open() with a positive result.
     * @return If connection is correctly created the valid handle otherwise a nullptr.
     */
    sqlite3 *getRawHandle() const noexcept;

private:
    sqlite3 *mHandle;
};

} // namespace LaptimerCore::Private::SqliteHelper

#endif // CONNECTION_HPP

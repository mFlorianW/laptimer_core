#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "Connection.hpp"
#include <optional>
#include <sqlite3.h>

namespace LaptimerCore::Storage::Private
{

enum class PrepareResult
{
    Ok,
    Error
};

enum class BindResult
{
    Ok,
    InvalidIndex,
    Error
};

enum class ExecuteResult
{
    Ok,
    Busy,
    Row,
    Error
};

enum class HasColumnValueResult
{
    Ok,
    Null
};

enum class ColumnType
{
    Integer = 1,
    Float = 2,
    Text = 3,
    Blob = 4,
    Null = 5
};

/**
 * A SQLite prepare statement
 */
class Statement final
{
public:
    /**
     * Constructs the statement object.
     * @param connection The db connection that shall be used to communicate with database. The connection must live as
     * long as the statment class.
     */
    Statement(const Connection &dbConnection);

    /**
     * Default destructor finialize the statement if necessary.
     */
    ~Statement();

    /**
     * Deleted copy constructor
     */
    Statement(const Statement &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    Statement &operator=(const Statement &other) = delete;

    /**
     * Deleted move constructor
     */
    Statement(Statement &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    Statement &operator=(Statement &&other) = delete;

    /**
     * Prepares the statment for furhter use.
     * @param connection The database connection.
     * @param statement The state that shall be prepared.
     * @return "Ok" Everything went fine and the statement is ready for further use.
     * @return "Error" In case of error. Check the DB connection error message.
     */
    PrepareResult prepare(const char *statement) noexcept;

    /**
     * Excutes the statement. Import is that the statement is prepared before calling execute.
     * @return "Ok" on success, the statement is successful executed and there is not more data to fetch.
     * @return "Busy" if it fails to require the lock
     * @return "Row" the statment is executed and there is still data to fetch.
     * @return "Error" in any other error case.
     */
    ExecuteResult execute() noexcept;

    /**
     * Resets the statement so it can be used with a different statement. Every fetched data is cleared.
     */
    void reset();

    /**
     * Binds a int value to the given index.
     * @param index The index of the value in the prepared statement.
     * @param value The value for the placeholder in the statement.
     * @return "Ok" Value is succesful binded.
     * @return "InvalidIndex" The index of the value is not valid.
     * @return "Error" for any other error. Check the error message of the connection.
     */
    BindResult bindIntValue(std::size_t index, std::int32_t value) noexcept;

    /**
     * Binds a string value to the statement under the given index.
     * @param index The index that shall be bind.
     * @param string The string value that shall be replaced in the statement.
     * @return "Ok" Value is succesful binded.
     * @return "InvalidIndex" The index of the value is not valid.
     * @return "Error" for any other error. Check the error message of the connection.
     */
    BindResult bindStringValue(std::size_t index, const std::string &value);

    /**
     * Gives the number of columns of the result. The value is zero when the statement doesn't select anything from the
     * database, e.g. UPDATE. The column count is zero when the statement isn't prepared and not succesful executed.
     * @return The number of columns in the result.
     */
    std::size_t getColumnCount() const noexcept;

    /**
     * Gives the type for the specific column type. Is the index out of range the ColumnTpye::Null is returned.
     * @return The column type.
     */
    ColumnType getColumnType(std::size_t index) const noexcept;

    /**
     * Checks if the column has a value.
     * @return "Ok" The column has a value
     * @return "Null" The column has no value
     */
    HasColumnValueResult hasColumnValue(std::size_t index) const noexcept;

    /**
     * Gives the int value for the index.
     * @param index The index of the column in the result row.
     * @return std::nullopt when failed to convert the value to int or the index is not in the range.
     */
    std::optional<std::int32_t> getIntColumn(std::size_t index) const noexcept;

    /**
     * Gives the float value for the index.
     * @param index The index of the column in the result row.
     * @return std::nullopt when failed to convert the value to int or the index is not in the range.
     */
    std::optional<float> getFloatColumn(std::size_t index) const noexcept;

    /**
     * Gives the string value for the index.
     * @param index The index of the column in the result row.
     * @return std::nullopt when failed to convert the value to int or the index is not in the range.
     */
    std::optional<std::string> getStringColumn(std::size_t index) const noexcept;

private:
    sqlite3_stmt *mStatement{nullptr};
    const Connection &mDbConnection;
};

} // namespace LaptimerCore::Storage::Private

#endif // STATEMENT_HPP

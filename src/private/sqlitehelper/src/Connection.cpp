#include "Connection.hpp"

namespace LaptimerCore::Private::SqliteHelper
{

Connection::~Connection()
{
    if (mHandle != nullptr)
    {
        sqlite3_close(mHandle);
    }
}

OpenResult Connection::open(const std::string &database)
{
    if (mHandle != nullptr)
    {
        sqlite3_close(mHandle);
    }

    if (sqlite3_open(database.c_str(), &mHandle))
    {
        return OpenResult::Ok;
    }

    return OpenResult::Error;
}

std::string Connection::getErrorMessage()
{
    if (mHandle != nullptr)
    {
        return sqlite3_errmsg(mHandle);
    }

    return {};
}

sqlite3 *Connection::getRawHandle() const noexcept
{
    if (mHandle == nullptr)
    {
        return nullptr;
    }

    return mHandle;
}

} // namespace LaptimerCore::Private::SqliteHelper

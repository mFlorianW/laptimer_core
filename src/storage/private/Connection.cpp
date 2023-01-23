#include "Connection.hpp"
#include <iostream>

namespace LaptimerCore::Storage::Private
{

Connection &Connection::connection(const std::string &database)
{
    static auto connection = Connection{database};
    return connection;
}

Connection::~Connection()
{
    if (mHandle != nullptr)
    {
        sqlite3_close(mHandle);
    }
}

Connection::Connection(const std::string &database)
{
    if (mHandle != nullptr)
    {
        sqlite3_close(mHandle);
    }

    if (sqlite3_open_v2(database.c_str(),
                        &mHandle,
                        SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_PRIVATECACHE,
                        nullptr) == SQLITE_OK)
    {
        sqlite3_exec(mHandle, "PRAGMA foreign_keys = 1", nullptr, nullptr, nullptr);
        return;
    }

    std::cout << "Exiting failed to create database connection. Error: " << getErrorMessage() << std::endl;
    std::exit(255);
}

std::string Connection::getErrorMessage() const noexcept
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

} // namespace LaptimerCore::Storage::Private

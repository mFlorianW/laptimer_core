#include "MemorySessionDatabaseBackend.hpp"

namespace LaptimerCore::Test::Dummy
{

MemorySessionDatabaseBackend::MemorySessionDatabaseBackend()
{
}

std::size_t MemorySessionDatabaseBackend::getLastStoredIndex() const noexcept
{
    if (!mStoredSessions.empty())
    {
        return mStoredSessions.back().id;
    }

    return 0;
}

std::size_t MemorySessionDatabaseBackend::getNumberOfStoredSessions() const noexcept
{
    return mStoredSessions.size();
}

bool MemorySessionDatabaseBackend::storeSession(std::size_t index, const std::string &sessionData)
{
    auto entry = Entry{.id = index, .data = sessionData};
    mStoredSessions.push_back(entry);
    return true;
}

std::string MemorySessionDatabaseBackend::loadSessionByIndex(std::size_t index)
{
    for (const auto &entry : mStoredSessions)
    {
        if (entry.id == index)
        {
            return entry.data;
        }
    }
    return "";
}

} // namespace LaptimerCore::Test::Dummy

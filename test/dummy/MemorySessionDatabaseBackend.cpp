#include "MemorySessionDatabaseBackend.hpp"

namespace LaptimerCore::Test::Dummy
{

MemorySessionDatabaseBackend::MemorySessionDatabaseBackend()
{
}

std::size_t MemorySessionDatabaseBackend::getLastStoredIndex() const noexcept
{
    if (mLastStoredSession.first == mStoredSessions.cend())
    {
        return 0;
    }

    return mLastStoredSession.first->first;
}

std::vector<std::size_t> MemorySessionDatabaseBackend::getIndexList() const noexcept
{
    auto result = std::vector<std::size_t>{};
    for (const auto &[key, rawSessioData] : mStoredSessions)
    {
        result.push_back(key);
    }

    return result;
}

std::size_t MemorySessionDatabaseBackend::getNumberOfStoredSessions() const noexcept
{
    return mStoredSessions.size();
}

bool MemorySessionDatabaseBackend::storeSession(std::size_t index, const std::string &sessionData)
{
    mLastStoredSession = mStoredSessions.insert({index, sessionData});
    return true;
}

std::string MemorySessionDatabaseBackend::loadSessionByIndex(std::size_t index)
{
    return mStoredSessions[index];
}

bool MemorySessionDatabaseBackend::deleteSession(std::size_t index)
{
    if (mStoredSessions.erase(index))
    {
        return true;
    }

    return false;
}

} // namespace LaptimerCore::Test::Dummy

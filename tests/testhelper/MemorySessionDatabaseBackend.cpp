// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MemorySessionDatabaseBackend.hpp"

namespace Rapid::TestHelper
{

MemorySessionDatabaseBackend::MemorySessionDatabaseBackend()
{
}

std::size_t MemorySessionDatabaseBackend::getLastStoredIndex() const noexcept
{
    if (mLastStoredSession.first == mStoredSessions.cend()) {
        return 0;
    }

    return mLastStoredSession.first->first;
}

std::vector<std::size_t> MemorySessionDatabaseBackend::getIndexList() const noexcept
{
    auto result = std::vector<std::size_t>{};
    for (auto const& [key, rawSessioData] : mStoredSessions) {
        result.push_back(key);
    }

    return result;
}

std::size_t MemorySessionDatabaseBackend::getNumberOfStoredSessions() const noexcept
{
    return mStoredSessions.size();
}

bool MemorySessionDatabaseBackend::storeSession(std::size_t index, std::string const& sessionData)
{
    if (mStoredSessions.count(index)) {
        mStoredSessions[index] = sessionData;
    } else {
        mLastStoredSession = mStoredSessions.insert({index, sessionData});
    }
    return true;
}

std::string MemorySessionDatabaseBackend::loadSessionByIndex(std::size_t index)
{
    return mStoredSessions[index];
}

bool MemorySessionDatabaseBackend::deleteSession(std::size_t index)
{
    if (mStoredSessions.erase(index)) {
        return true;
    }

    return false;
}

} // namespace Rapid::TestHelper

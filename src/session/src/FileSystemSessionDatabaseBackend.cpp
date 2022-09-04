#include "FileSystemSessionDatabaseBackend.hpp"
#include <filesystem>
#include <fstream>

namespace LaptimerCore::Session
{

FileSystemSessionDatabaseBackend::FileSystemSessionDatabaseBackend(const std::string &databaseFolder)
    : mDbDir{databaseFolder}
{
}

size_t FileSystemSessionDatabaseBackend::getLastStoredIndex() const noexcept
{
    return mLastStoredIndex;
}

std::vector<std::size_t> FileSystemSessionDatabaseBackend::getIndexList() const noexcept
{
    return std::vector<std::size_t>();
}

size_t FileSystemSessionDatabaseBackend::getNumberOfStoredSessions() const noexcept
{
    return 0;
}

bool FileSystemSessionDatabaseBackend::storeSession(std::size_t index, const std::string &sessionData)
{
    if (!std::filesystem::exists(mDbDir))
    {
        return false;
    }

    auto fileName = std::string{"session"} + std::to_string(index);

    std::ofstream sessionFile(mDbDir + "/" + fileName + ".json");
    sessionFile << sessionData;
    sessionFile.close();

    mLastStoredIndex = index;
    return true;
}

std::string FileSystemSessionDatabaseBackend::loadSessionByIndex(std::size_t index)
{
    auto sessionPath = mDbDir + "/" + "session" + std::to_string(index) + ".json";
    auto file = std::ifstream{};
    auto strBuffer = std::stringstream{};

    file.open(sessionPath);
    strBuffer << file.rdbuf();

    return strBuffer.str();
}

bool FileSystemSessionDatabaseBackend::deleteSession(std::size_t index)
{
    return false;
}

} // namespace LaptimerCore::Session

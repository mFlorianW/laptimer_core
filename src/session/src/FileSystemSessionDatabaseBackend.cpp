#include "FileSystemSessionDatabaseBackend.hpp"
#include <algorithm>
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
    auto result = std::vector<std::size_t>();
    for (const auto &entry : std::filesystem::directory_iterator{mDbDir})
    {
        if (entry.is_regular_file() && (entry.path().filename().string().rfind("session", 0) == 0))
        {
            auto tempString = entry.path().filename().string().erase(0, std::string{"session"}.length());
            auto fileEndingIter = tempString.find(".json");
            tempString = tempString.erase(fileEndingIter, std::string{".json"}.length());
            auto index = stoi(tempString);
            result.insert(result.begin(), index);
        }
    }

    // Gurantee ascending order of the index list.
    std::sort(result.begin(), result.end());
    return result;
}

size_t FileSystemSessionDatabaseBackend::getNumberOfStoredSessions() const noexcept
{
    std::size_t numberOfStoredSessions = 0;
    for (const auto &entry : std::filesystem::directory_iterator{mDbDir})
    {
        if (entry.is_regular_file() && (entry.path().filename().string().rfind("session", 0) == 0))
        {
            ++numberOfStoredSessions;
        }
    }
    return numberOfStoredSessions;
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

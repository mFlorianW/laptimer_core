#ifndef MEMORYSESSIONDATABASE_HPP
#define MEMORYSESSIONDATABASE_HPP

#include "ISessionDatabaseBackend.hpp"
#include <map>

namespace LaptimerCore::Test::Dummy
{

class MemorySessionDatabaseBackend : public LaptimerCore::Session::ISessionDatabaseBackend
{
public:
    MemorySessionDatabaseBackend();

    std::size_t getLastStoredIndex() const noexcept override;
    std::vector<std::size_t> getIndexList() const noexcept override;
    std::size_t getNumberOfStoredSessions() const noexcept override;
    bool storeSession(std::size_t index, const std::string &sessionData) override;
    std::string loadSessionByIndex(std::size_t index) override;
    bool deleteSession(std::size_t index) override;

private:
    std::map<std::size_t, std::string> mStoredSessions;
    std::pair<std::map<std::size_t, std::string>::const_iterator, bool> mLastStoredSession;
};

} // namespace LaptimerCore::Test::Dummy

#endif // MEMORYSESSIONDATABASE_HPP

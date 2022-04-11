#ifndef MEMORYSESSIONDATABASE_HPP
#define MEMORYSESSIONDATABASE_HPP

#include "ISessionDatabaseBackend.hpp"
#include <vector>

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
    struct Entry
    {
        std::size_t id;
        std::string data;
    };

    std::vector<Entry> mStoredSessions;
};

} // namespace LaptimerCore::Test::Dummy

#endif // MEMORYSESSIONDATABASE_HPP

#ifndef ISESIONDATABASEBACKEND_HPP
#define ISESIONDATABASEBACKEND_HPP

#include <ArduinoJson.hpp>
#include <cstdint>
#include <vector>

namespace LaptimerCore::Storage
{

class ISessionDatabaseBackend
{
public:
    virtual ~ISessionDatabaseBackend() = default;

    virtual std::size_t getLastStoredIndex() const noexcept = 0;

    virtual std::vector<std::size_t> getIndexList() const noexcept = 0;

    virtual std::size_t getNumberOfStoredSessions() const noexcept = 0;

    virtual bool storeSession(std::size_t index, const std::string &sessionData) = 0;

    virtual std::string loadSessionByIndex(std::size_t index) = 0;

    virtual bool deleteSession(std::size_t index) = 0;

protected:
    ISessionDatabaseBackend() = default;
};

} // namespace LaptimerCore::Storage

#endif // ISESIONDATABASEBACKEND_HPP

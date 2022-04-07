#ifndef ISESIONDATABASEBACKEND_HPP
#define ISESIONDATABASEBACKEND_HPP

#include <ArduinoJson.hpp>
#include <cstdint>

namespace LaptimerCore::Session
{

class ISessionDatabaseBackend
{
public:
    virtual ~ISessionDatabaseBackend() = default;

    virtual std::size_t getNumberOfStoredSessions() const noexcept = 0;

    virtual bool storeSession(std::size_t index, const std::string &sessionData) = 0;

    virtual std::string loadSessionByIndex(std::size_t index) = 0;

protected:
    ISessionDatabaseBackend() = default;
};

} // namespace LaptimerCore::Session

#endif // ISESIONDATABASEBACKEND_HPP

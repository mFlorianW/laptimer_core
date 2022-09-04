#ifndef JSONDESERIALIZER_HPP
#define JSONDESERIALIZER_HPP

#include "SessionData.hpp"
#include <ArduinoJson.h>
#include <optional>
#include <string>

namespace LaptimerCore::Common
{
class JsonDeserializer
{
public:
    static std::optional<SessionData> deserializeSessionData(const std::string &rawData);
};

} // namespace LaptimerCore::Common

#endif // JSONDESERIALIZER_HPP
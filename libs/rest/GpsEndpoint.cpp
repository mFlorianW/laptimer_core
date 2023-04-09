#include "GpsEndpoint.hpp"
#include "RestRequest.hpp"
#include <ArduinoJson.hpp>

using namespace LaptimerCore::Common;

namespace LaptimerCore::Rest
{
GpsEndpoint::GpsEndpoint() = default;
GpsEndpoint::~GpsEndpoint() = default;

RequestHandleResult GpsEndpoint::handleRestRequest(RestRequest &request) noexcept
{
    auto jsonDoc = ArduinoJson::DynamicJsonDocument{512};
    if ((ArduinoJson::deserializeJson(jsonDoc, request.getRequestBody()) != ArduinoJson::DeserializationError::Ok) &&
        jsonDoc.containsKey("date") && jsonDoc.containsKey("time") && jsonDoc.containsKey("latitude") &&
        jsonDoc.containsKey("longitude"))
    {
        return RequestHandleResult::Error;
    }
    auto newPos = PositionDateTimeData{};
    newPos.setDate({jsonDoc["date"].as<std::string>()});
    newPos.setTime({jsonDoc["time"].as<std::string>()});
    newPos.setPosition(
        {std::stof(jsonDoc["latitude"].as<std::string>()), std::stof(jsonDoc["longitude"].as<std::string>())});

    positionTimeData = newPos;

    return RequestHandleResult::Ok;
}
} // namespace LaptimerCore::Rest

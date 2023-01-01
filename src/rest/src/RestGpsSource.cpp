#include "RestGpsSource.hpp"
#include "RestRequest.hpp"
#include <ArduinoJson.hpp>

using namespace LaptimerCore::Common;

namespace LaptimerCore::Rest
{
RestGpsSource::RestGpsSource() = default;
RestGpsSource::~RestGpsSource() = default;

RequestHandleResult RestGpsSource::handleRestRequest(const RestRequest &request)
{
    auto jsonDoc = ArduinoJson::StaticJsonDocument<1024>{};
    if ((ArduinoJson::deserializeJson(jsonDoc, request.getRawData()) != ArduinoJson::DeserializationError::Ok) &&
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

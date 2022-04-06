#include "JsonSerializer.hpp"

namespace LaptimerCore::Common
{

bool JsonSerializer::serializeTrackData(const TrackData &trackData, JsonObject &jsonObject)
{
    jsonObject["name"] = trackData.getTrackName();

    auto startlineObject = jsonObject.createNestedObject("startline");
    JsonSerializer::serializePositionData(trackData.getStartline(), startlineObject);

    auto finishlineObject = jsonObject.createNestedObject("finishline");
    JsonSerializer::serializePositionData(trackData.getFinishline(), finishlineObject);

    if (trackData.getNumberOfSections() > 0)
    {
        auto sectorList = jsonObject.createNestedArray("sectors");
        for (std::size_t i = 0; i < trackData.getNumberOfSections(); ++i)
        {
            auto sectorObject = sectorList.createNestedObject();
            JsonSerializer::serializePositionData(trackData.getSection(i), sectorObject);
        }
    }

    return true;
}

bool JsonSerializer::serializeLapData(const LapData &lapData, JsonObject &jsonObject)
{
    if (lapData.getSectorTimeCount() > 0)
    {
        auto jsonSectorTimes = jsonObject.createNestedArray("sectors");
        for (std::size_t i = 0; i < lapData.getSectorTimeCount(); ++i)
        {
            jsonSectorTimes.add(lapData.getSectorTime(i).value().asString());
        }
    }

    return true;
}

bool JsonSerializer::serializePositionData(const PositionData &posData, JsonObject &jsonObject)
{
    jsonObject["latitude"] = std::to_string(posData.getLatitude());
    jsonObject["longitude"] = std::to_string(posData.getLongitude());

    return true;
}

bool JsonSerializer::serializeSessionData(const SessionData &sessionData, JsonObject &jsonObject)
{
    jsonObject["date"] = sessionData.getSessionDate().asString();
    jsonObject["time"] = sessionData.getSessionTime().asString();
    auto trackObject = jsonObject.createNestedObject("track");
    JsonSerializer::serializeTrackData(sessionData.getTrack(), trackObject);
    if (sessionData.getNumberOfLaps() > 0)
    {
        auto lapArray = jsonObject.createNestedArray("laps");
        for (const auto &lap : std::as_const(sessionData.getLaps()))
        {
            auto lapObject = lapArray.createNestedObject();
            serializeLapData(lap, lapObject);
        }
    }

    return true;
}

} // namespace LaptimerCore::Common

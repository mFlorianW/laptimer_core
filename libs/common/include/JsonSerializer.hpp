#ifndef JSONSERIALIZER_HPP
#define JSONSERIALIZER_HPP

#include "LapData.hpp"
#include "SessionData.hpp"
#include "TrackData.hpp"
#include <ArduinoJson.h>

namespace LaptimerCore::Common
{

class JsonSerializer
{
public:
    /**
     * Serialize the track data into the given JSON object.
     * @param trackData The data that shall be serialized.
     * @param jsonObject The target object of the serialized track data.
     * @return True succuessful serialized otherwise false.
     */
    static bool serializeTrackData(const TrackData &trackData, ArduinoJson::JsonObject &jsonObject);

    /**
     * Serialize the lap data into the given JSON object.
     * @param lapData The data that shall be serialized.
     * @param jsonObject The target object of the serialized track data.
     * @return True succuessful serialized otherwise false.
     */
    static bool serializeLapData(const LapData &lapData, ArduinoJson::JsonObject &jsonObject);

    /**
     * Serialize the position data into the given JSON object.
     * @param posData The data that shall be serialized.
     * @param jsonObject The target object of the serialized track data.
     * @return True succuessful serialized otherwise false.
     */
    static bool serializePositionData(const PositionData &posData, ArduinoJson::JsonObject &jsonObject);

    /**
     * Serialize the session data into the given JSON object.
     * @param sessionData The data that shall be serialized.
     * @param jsonObject The target object of the serialized track data.
     * @return True succuessful serialized otherwise false.
     */
    static bool serializeSessionData(const SessionData &sessionData, ArduinoJson::JsonObject &jsonObject);
};

} // namespace LaptimerCore::Common

#endif // JSONSERIALIZER_HPP

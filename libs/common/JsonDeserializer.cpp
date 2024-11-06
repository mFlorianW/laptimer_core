// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "JsonDeserializer.hpp"

namespace Rapid::Common
{

namespace
{
std::optional<TrackData> deserializeTrackData(ArduinoJson::JsonObject const& object)
{
    TrackData trackData;
    auto trackName = object["name"].as<std::string>();
    trackData.setTrackName(trackName);

    try {
        auto startlineObj = object["startline"];
        auto startlinelong = std::stof(startlineObj["longitude"].as<std::string>());
        auto startlineLat = std::stof(startlineObj["latitude"].as<std::string>());

        PositionData startline;
        startline.setLongitude(startlinelong);
        startline.setLatitude(startlineLat);
        trackData.setStartline(startline);

        auto finishlineObj = object["finishline"];
        auto linelong = std::stof(finishlineObj["longitude"].as<std::string>());
        auto lineLat = std::stof(finishlineObj["latitude"].as<std::string>());

        PositionData finishline;
        finishline.setLongitude(linelong);
        finishline.setLatitude(lineLat);
        trackData.setFinishline(finishline);

        auto sectorsArray = object["sectors"].as<ArduinoJson::JsonArray>();
        std::vector<PositionData> sectors;
        sectors.reserve(sectorsArray.size());
        for (ArduinoJson::JsonVariant const& v : sectorsArray) {
            auto sectorObj = v.as<ArduinoJson::JsonObject>();
            auto sectorLong = std::stof(sectorObj["longitude"].as<std::string>());
            auto sectorLatitude = std::stof(sectorObj["latitude"].as<std::string>());

            PositionData sector;
            sector.setLongitude(sectorLong);
            sector.setLatitude(sectorLatitude);
            sectors.push_back(sector);
        }
        trackData.setSections(sectors);
    } catch (std::invalid_argument& e) {
    } catch (std::out_of_range& e) {
    }

    return trackData;
}

std::vector<LapData> deserializeLapData(ArduinoJson::JsonArray const& lapArray)
{
    std::vector<LapData> laps;
    for (ArduinoJson::JsonVariant const& v : lapArray) {
        LapData lap;
        auto lapTimeArray = v["sectors"].as<ArduinoJson::JsonArray>();
        for (ArduinoJson::JsonVariant const& rawLapData : lapTimeArray) {
            auto time = Timestamp(rawLapData.as<std::string>());
            lap.addSectorTime(time);
        }

        laps.push_back(lap);
    }

    return laps;
}

} // namespace

std::optional<SessionData> JsonDeserializer::deserializeSessionData(std::string const& rawData)
{
    //    auto jsonDoc = ArduinoJson::DynamicJsonDocument{rawData.capacity()};
    auto jsonDoc = ArduinoJson::StaticJsonDocument<8192>{};
    ArduinoJson::deserializeJson(jsonDoc, rawData);
    auto sessionDate = Date(jsonDoc["date"].as<std::string>());
    auto sessionTime = Timestamp(jsonDoc["time"].as<std::string>());
    auto trackData = deserializeTrackData(jsonDoc["track"]).value();
    auto laps = deserializeLapData(jsonDoc["laps"]);

    auto session = SessionData{trackData, sessionDate, sessionTime};
    for (auto const& lap : laps) {
        session.addLap(lap);
    }

    return {session};
}

} // namespace Rapid::Common

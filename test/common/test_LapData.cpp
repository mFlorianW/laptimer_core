#define CATCH_CONFIG_MAIN
#include "LapData.hpp"
#include "Timestamp.hpp"
#include <ArduinoJson.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;

TEST_CASE("The lap data shall serialize the laptime without sector into a JSON document.")
{
    constexpr char expectedResult[] = "{\"laptime\":\"00:01:35.123\"}";
    Timestamp lapTime;
    lapTime.setHour(0);
    lapTime.setMinute(1);
    lapTime.setSecond(35);
    lapTime.setFractionalOfSecond(123);
    LapData lap;
    lap.setLaptime(lapTime);

    std::string result;
    ArduinoJson::serializeJson(lap.asJson(), result);

    REQUIRE(result == expectedResult);
}

TEST_CASE("The LapData shall serialize the sectors into a JSON array into a JSON document")
{
    // clang-format off
    constexpr char expectedResult[] =
        "{"
        "\"laptime\":\"00:01:35.123\","
        "\"sectors\":["
            "{"
              "\"sector0\":\"00:00:25.134\""
            "},"
            "{"
              "\"sector1\":\"00:00:25.144\""
             "}"
         "]"
         "}";
    // clang-format on
    Timestamp lapTime;
    lapTime.setHour(0);
    lapTime.setMinute(1);
    lapTime.setSecond(35);
    lapTime.setFractionalOfSecond(123);
    Timestamp sectorTime1;
    sectorTime1.setHour(0);
    sectorTime1.setMinute(0);
    sectorTime1.setSecond(25);
    sectorTime1.setFractionalOfSecond(134);
    Timestamp sectorTime2;
    sectorTime2.setHour(0);
    sectorTime2.setMinute(0);
    sectorTime2.setSecond(25);
    sectorTime2.setFractionalOfSecond(144);
    LapData lap;
    lap.setLaptime(lapTime);
    lap.addSectorTime(sectorTime1);
    lap.addSectorTime(sectorTime2);

    std::string result;
    ArduinoJson::serializeJson(lap.asJson(), result);

    REQUIRE(result == expectedResult);
}

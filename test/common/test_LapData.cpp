#define CATCH_CONFIG_MAIN
#include "LapData.hpp"
#include "Timestamp.hpp"
#include <ArduinoJson.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;

TEST_CASE("The LapData shall calculate the laptime by the sector times.")
{
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
    lap.addSectorTime(sectorTime1);
    lap.addSectorTime(sectorTime2);

    REQUIRE(lap.getLaptime().getHour() == 0);
    REQUIRE(lap.getLaptime().getMinute() == 0);
    REQUIRE(lap.getLaptime().getSecond() == 50);
    REQUIRE(lap.getLaptime().getFractionalOfSecond() == 278);
}

TEST_CASE("The LapData shall serialize the sectors into a JSON array into a JSON document")
{
    // clang-format off
    constexpr char expectedResult[] =
        "{"
        "\"sectors\":["
              "\"00:00:25.134\","
              "\"00:00:25.144\""
         "]"
         "}";
    // clang-format on
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
    lap.addSectorTime(sectorTime1);
    lap.addSectorTime(sectorTime2);

    std::string result;
    ArduinoJson::serializeJson(lap.asJson(), result);

    REQUIRE(result == expectedResult);
}

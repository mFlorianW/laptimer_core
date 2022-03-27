#define CATCH_CONFIG_MAIN
#include "PositionData.hpp"
#include "Positions.hpp"
#include <ArduinoJson.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The TrackData shall be able to serialize to a JSON document.")
{
    constexpr char expectedJsonObject[] = "{\"latitude\":\"52.025833\",\"longitude\":\"11.279166\"}";
    Positions::init();

    auto jsonObject = Positions::OscherslebenPosition.asJson();
    std::string result;
    ArduinoJson::serializeJson(jsonObject, result);

    REQUIRE(result == expectedJsonObject);
}

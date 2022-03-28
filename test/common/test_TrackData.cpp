#define CATCH_CONFIG_MAIN
#include "Positions.hpp"
#include "TrackData.hpp"
#include "Tracks.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The TrackData shall serialize the TrackData without sector into a JSON object")
{
    // clang-format off
    constexpr char expectedJson[] = "{"
        "\"name\":\"TrackWithoutSector\","
        "\"startline\":{"
            "\"latitude\":\"52.025833\","
            "\"longitude\":\"11.279166\""
        "},"
        "\"finishline\":{"
            "\"latitude\":\"52.025833\","
            "\"longitude\":\"11.279166\""
        "}"
    "}";
    // clang-format on
    Positions::init();
    Tracks::init();

    auto jsonObject = Tracks::TrackWithoutSector.asJson();
    std::string result;
    ArduinoJson::serializeJson(jsonObject, result);

    REQUIRE(result == expectedJson);
}

TEST_CASE("The TrackData shall serialize the TrackData into a JSON object")
{
    // clang-format off
    constexpr char expectedJson[] = "{"
        "\"name\":\"Oschersleben\","
        "\"startline\":{"
            "\"latitude\":\"52.025833\","
            "\"longitude\":\"11.279166\""
        "},"
        "\"finishline\":{"
            "\"latitude\":\"52.025833\","
            "\"longitude\":\"11.279166\""
        "},"
        "\"sectors\":["
            "{"
                "\"latitude\":\"52.025833\","
                "\"longitude\":\"11.279166\""
            "},"
            "{"
                "\"latitude\":\"52.025833\","
                "\"longitude\":\"11.279166\""
            "}"
        "]"
    "}";
    // clang-format on
    Positions::init();
    Tracks::init();

    auto jsonObject = Tracks::OscherslebenTrack.asJson();
    std::string result;
    ArduinoJson::serializeJson(jsonObject, result);

    REQUIRE(result == expectedJson);
}

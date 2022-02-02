#define CATCH_CONFIG_MAIN
#include "TrackDetection.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::Algorithm;

TEST_CASE("Return true when position is on the track.")
{
    auto trackDetection = TrackDetection{500};
    // clang-format off
    auto oscherslebenTrack = TrackData{};
    auto finishLine =  PositionData
    {
        .latitude = 52.02718520,
        .longitude = 11.27989104,
    };
    oscherslebenTrack.setFinishline(finishLine);

    auto positionTest = PositionData
    {
        .latitude = 52.0258333,
        .longitude = 11.279166666,
    };
    // clang-format on

    REQUIRE(trackDetection.isOnTrack(oscherslebenTrack, positionTest) == true);
}

TEST_CASE("Return false when position is not on the track.")
{
    auto trackDetection = TrackDetection{500};
    // clang-format off
    auto oscherslebenTrack = TrackData{};
    auto finishLine =  PositionData
    {
        .latitude = 52.02718520,
        .longitude = 11.27989104,
    };
    oscherslebenTrack.setFinishline(finishLine);

    auto invalidPositionData = PositionData
    {
        .latitude = 52.0225,
        .longitude = 11.277777777777779,
    };
    // clang-format on

    REQUIRE(trackDetection.isOnTrack(oscherslebenTrack, invalidPositionData) == false);
}
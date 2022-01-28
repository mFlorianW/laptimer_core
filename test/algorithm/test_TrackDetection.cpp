#define CATCH_CONFIG_MAIN
#include "TrackDetection.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::Algorithm;

TEST_CASE("Return true when position is on the track.")
{
    auto trackDetection = TrackDetection{};

    // REQUIRE(trackDetection.isOnTrack(TrackData{}, PositionData{}) == true);
}
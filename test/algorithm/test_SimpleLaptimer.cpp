#define CATCH_CONFIG_MAIN
#include "Positions.hpp"
#include "SimpleLaptimer.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Algorithm;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The laptimer shall emit lapStarted Signal when crossing the start line. Case1")
{
    SimpleLaptimer timer;
    bool callback_called = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionFinishLine);

    timer.setTrack(track);
    timer.lapStarted.connect([&callback_called](void) { callback_called = true; });

    auto gpsPoint1 = PositionDateTimeData{{52.0270444630482, 11.28054316951109}, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{{52.0270730501194, 11.28042347580554}, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{{52.02710841143324, 11.2802563754895}, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{{52.02714389003916, 11.28008359503905}, {}, {}};

    timer.setTrack(track);
    timer.updatePositionAndTime(gpsPoint1);
    timer.updatePositionAndTime(gpsPoint2);
    timer.updatePositionAndTime(gpsPoint3);
    timer.updatePositionAndTime(gpsPoint4);

    REQUIRE(callback_called == true);
}

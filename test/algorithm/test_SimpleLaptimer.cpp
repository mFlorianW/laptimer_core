#define CATCH_CONFIG_MAIN
#include "Positions.hpp"
#include "SimpleLaptimer.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Algorithm;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The laptimer shall emit lapStarted Signal when crossing the start line. Case1")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });

    auto gpsPoint1 = PositionDateTimeData{{52.0270444, 11.2805431}, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{{52.0270730, 11.2804234}, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{{52.0271084, 11.2802563}, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{{52.0271438, 11.2800835}, {}, {}};

    lapTimer.setTrack(track);
    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapStartedEmitted == true);
}

TEST_CASE("The laptimer shall call the lap started callback when crossing the start line. Case2")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });

    auto gpsPoint1 = PositionDateTimeData{{52.0270444, 11.2805431}, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{{52.0270730, 11.2804234}, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{{52.0270945, 11.2803176}, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{{52.0271438, 11.2800835}, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapStartedEmitted == true);
}

TEST_CASE("The laptimer shall emit the lap finished signal and lap started signal when completing a lap.")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;
    bool lapFinishedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionFinishLine);
    track.setFinishline(Positions::OscherslebenPositionFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });
    lapTimer.lapFinished.connect([&lapFinishedEmitted](void) { lapFinishedEmitted = true; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{{52.0270444, 11.2805431}, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{{52.0270730, 11.2804234}, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{{52.0270945, 11.2803176}, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{{52.0271438, 11.2800835}, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    // Position to finish the lap
    auto gpsPoint5 = PositionDateTimeData{{52.0270444, 11.2805431}, {}, {}};
    auto gpsPoint6 = PositionDateTimeData{{52.0270730, 11.2804234}, {}, {}};
    auto gpsPoint7 = PositionDateTimeData{{52.0270945, 11.2803176}, {}, {}};
    auto gpsPoint8 = PositionDateTimeData{{52.0271438, 11.2800835}, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(lapFinishedEmitted == true);
    REQUIRE(lapStartedEmitted == true);
}

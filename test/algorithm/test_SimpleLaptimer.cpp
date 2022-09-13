#define CATCH_CONFIG_MAIN
#include "Positions.hpp"
#include "SimpleLaptimer.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Algorithm;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The laptimer shall emit lapStarted Signal when crossing the start line for the first time. Case1")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });

    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.setTrack(track);
    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapStartedEmitted == true);
}

TEST_CASE("The laptimer shall call the lap started callback when crossing the start line for the first time. Case2")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });

    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

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
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });
    lapTimer.lapFinished.connect([&lapFinishedEmitted](void) { lapFinishedEmitted = true; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    // Position to finish the lap
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(lapFinishedEmitted == true);
    REQUIRE(lapStartedEmitted == true);
}

TEST_CASE("The laptimer shall call the sector finished signal when a sector is finshed")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;
    bool sectorFinishedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setSections({Positions::OscherslebenPositionSector1Line});

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });
    lapTimer.sectorFinished.connect([&sectorFinishedEmitted](void) { sectorFinishedEmitted = true; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapStartedEmitted == true);

    // Positions to finsh a sector
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenSector1Point1, {}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenSector1Point2, {}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenSector1Point3, {}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenSector1Point4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(sectorFinishedEmitted == true);
}

TEST_CASE("The laptimer shall send all signals for a whole map.")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;
    bool sectorFinishedEmitted = false;
    bool lapFinishedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setSections({Positions::OscherslebenPositionSector1Line, Positions::OscherslebenPositionSector2Line});
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });
    lapTimer.sectorFinished.connect([&sectorFinishedEmitted](void) { sectorFinishedEmitted = true; });
    lapTimer.lapFinished.connect([&lapFinishedEmitted](void) { lapFinishedEmitted = true; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapStartedEmitted == true);

    // Positions to finsh sector1
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenSector1Point1, {}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenSector1Point2, {}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenSector1Point3, {}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenSector1Point4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(sectorFinishedEmitted == true);

    // Positions to finsh sector2
    sectorFinishedEmitted = false;
    auto gpsPoint9 = PositionDateTimeData{Positions::OscherslebenSector2Point1, {}, {}};
    auto gpsPoint10 = PositionDateTimeData{Positions::OscherslebenSector2Point2, {}, {}};
    auto gpsPoint11 = PositionDateTimeData{Positions::OscherslebenSector2Point3, {}, {}};
    auto gpsPoint12 = PositionDateTimeData{Positions::OscherslebenSector2Point4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint9);
    lapTimer.updatePositionAndTime(gpsPoint10);
    lapTimer.updatePositionAndTime(gpsPoint11);
    lapTimer.updatePositionAndTime(gpsPoint12);

    // Positions to start the lap
    lapStartedEmitted = false;
    auto gpsPoint13 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint14 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint15 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint16 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint13);
    lapTimer.updatePositionAndTime(gpsPoint14);
    lapTimer.updatePositionAndTime(gpsPoint15);
    lapTimer.updatePositionAndTime(gpsPoint16);

    REQUIRE(lapFinishedEmitted == true);
    REQUIRE(lapStartedEmitted == true);
}

TEST_CASE("The laptimer shall update the lap time after lap is started unit lap is finished with every "
          "time update. Lap is without sector")
{
    SimpleLaptimer lapTimer;
    std::uint32_t lapTimeUpdateCounter = 0;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);
    lapTimer.currentLaptime.valueChanged().connect(
        [&lapTimeUpdateCounter](Timestamp newTimeStamp) { ++lapTimeUpdateCounter; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:05:10.234"}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:05:11.234"}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:05:12.234"}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, Timestamp{"15:05:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapTimer.currentLaptime.get() == Timestamp{"00:00:00.000"});

    // Positions to finish the lap
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:06:10.234"}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:06:11.234"}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:06:12.234"}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, Timestamp{"15:06:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(lapTimeUpdateCounter == 6);
    REQUIRE(lapTimer.currentLaptime.get() == Timestamp{"00:00:00.000"});
    REQUIRE(lapTimer.getLastLaptime() == Timestamp{"00:01:00.000"});
}

TEST_CASE("The laptimer shall give the last lap time when lap is started and finished. Lap is without sector.")
{
    SimpleLaptimer lapTimer;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:05:10.234"}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:05:11.234"}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:05:12.234"}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, Timestamp{"15:05:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapTimer.currentLaptime.get() == Timestamp{"00:00:00.000"});

    // Positions to finish the lap
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:06:10.234"}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:06:11.234"}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:06:12.234"}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, Timestamp{"15:06:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(lapTimer.getLastLaptime() == Timestamp{"00:01:00.000"});
}

TEST_CASE("The laptimer shall give the last lap time when lap is started and finished. Lap is with sector.")
{
    SimpleLaptimer lapTimer;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setSections({Positions::OscherslebenPositionSector1Line});
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:05:10.234"}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:05:11.234"}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:05:12.234"}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, Timestamp{"15:05:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapTimer.currentLaptime.get() == Timestamp{"00:00:00.000"});

    // Positions to finsh sector1
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenSector1Point1, Timestamp{"15:06:10.234"}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenSector1Point2, Timestamp{"15:06:11.234"}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenSector1Point3, Timestamp{"15:06:12.234"}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenSector1Point4, Timestamp{"15:06:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(lapTimer.currentLaptime.get() == Timestamp{"00:01:00.000"});

    // Positions to finish the lap
    auto gpsPoint9 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:07:10.234"}, {}};
    auto gpsPoint10 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:07:11.234"}, {}};
    auto gpsPoint11 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:07:12.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint9);
    lapTimer.updatePositionAndTime(gpsPoint10);
    lapTimer.updatePositionAndTime(gpsPoint11);
    REQUIRE(lapTimer.getLastLaptime() == Timestamp{"00:01:59.000"});
}

TEST_CASE("The laptimer shall update the current sector time.")
{
    SimpleLaptimer lapTimer;
    std::uint32_t currentSectorTimeUpdated = 0;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setSections({Positions::OscherslebenPositionSector1Line, Positions::OscherslebenPositionSector2Line});
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);

    lapTimer.setTrack(track);
    lapTimer.currentSectorTime.valueChanged().connect(
        [&currentSectorTimeUpdated](Timestamp newTimestamp) { ++currentSectorTimeUpdated; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:05:10.234"}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:05:11.234"}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:05:12.234"}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, Timestamp{"15:05:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:00.000"});

    // Positions to finsh sector1
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenSector1Point1, Timestamp{"15:06:10.234"}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenSector1Point2, Timestamp{"15:06:11.234"}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenSector1Point3, Timestamp{"15:06:12.234"}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenSector1Point4, Timestamp{"15:06:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    REQUIRE(currentSectorTimeUpdated == 1);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:57.000"});
    lapTimer.updatePositionAndTime(gpsPoint6);
    REQUIRE(currentSectorTimeUpdated == 2);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:58.000"});

    // Sector1 is finshed here
    lapTimer.updatePositionAndTime(gpsPoint7);
    REQUIRE(currentSectorTimeUpdated == 4);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:00.000"});
    REQUIRE(lapTimer.getLastSectorTime() == Timestamp{"00:00:59.000"});
    lapTimer.updatePositionAndTime(gpsPoint8);
    REQUIRE(currentSectorTimeUpdated == 5);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:01.000"});

    // Positions to finsh sector2
    auto gpsPoint9 = PositionDateTimeData{Positions::OscherslebenSector2Point1, Timestamp{"15:07:10.234"}, {}};
    auto gpsPoint10 = PositionDateTimeData{Positions::OscherslebenSector2Point2, Timestamp{"15:07:11.234"}, {}};
    auto gpsPoint11 = PositionDateTimeData{Positions::OscherslebenSector2Point3, Timestamp{"15:07:12.234"}, {}};
    auto gpsPoint12 = PositionDateTimeData{Positions::OscherslebenSector2Point4, Timestamp{"15:07:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint9);
    REQUIRE(currentSectorTimeUpdated == 6);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:58.000"});
    lapTimer.updatePositionAndTime(gpsPoint10);
    REQUIRE(currentSectorTimeUpdated == 7);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:59.000"});
    lapTimer.updatePositionAndTime(gpsPoint11);
    REQUIRE(currentSectorTimeUpdated == 8);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:01:00.000"});
    // Sector2 finished here
    lapTimer.updatePositionAndTime(gpsPoint12);
    REQUIRE(currentSectorTimeUpdated == 10);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:00.000"});
    REQUIRE(lapTimer.getLastSectorTime() == Timestamp{"00:01:01.000"});

    // Positions to finish the lap
    auto gpsPoint13 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, Timestamp{"15:08:10.234"}, {}};
    auto gpsPoint14 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, Timestamp{"15:08:11.234"}, {}};
    auto gpsPoint15 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, Timestamp{"15:08:12.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint13);
    REQUIRE(currentSectorTimeUpdated == 11);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:57.000"});
    lapTimer.updatePositionAndTime(gpsPoint14);
    REQUIRE(currentSectorTimeUpdated == 12);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:58.000"});
    lapTimer.updatePositionAndTime(gpsPoint15);
    REQUIRE(currentSectorTimeUpdated == 14);
    REQUIRE(lapTimer.currentSectorTime.get() == Timestamp{"00:00:00.000"});
    REQUIRE(lapTimer.getLastSectorTime() == Timestamp{"00:00:59.000"});
}

TEST_CASE("The laptimer shall emit the signals sector and lap started finished even for two laps.")
{
    SimpleLaptimer lapTimer;
    bool lapStartedEmitted = false;
    bool lapFinishedEmitted = false;
    bool sectorFinishedEmitted = false;

    auto track = TrackData{};
    track.setStartline(Positions::OscherslebenPositionStartFinishLine);
    track.setFinishline(Positions::OscherslebenPositionStartFinishLine);
    track.setSections({Positions::OscherslebenPositionSector1Line});

    lapTimer.setTrack(track);
    lapTimer.lapStarted.connect([&lapStartedEmitted](void) { lapStartedEmitted = true; });
    lapTimer.lapFinished.connect([&lapFinishedEmitted](void) { lapFinishedEmitted = true; });
    lapTimer.sectorFinished.connect([&sectorFinishedEmitted](void) { sectorFinishedEmitted = true; });

    // Positions to start the lap
    auto gpsPoint1 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint2 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint3 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint4 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint1);
    lapTimer.updatePositionAndTime(gpsPoint2);
    lapTimer.updatePositionAndTime(gpsPoint3);
    lapTimer.updatePositionAndTime(gpsPoint4);

    REQUIRE(lapStartedEmitted == true);
    lapStartedEmitted = false;

    // Positions to finsh sector1
    auto gpsPoint5 = PositionDateTimeData{Positions::OscherslebenSector1Point1, Timestamp{"15:06:10.234"}, {}};
    auto gpsPoint6 = PositionDateTimeData{Positions::OscherslebenSector1Point2, Timestamp{"15:06:11.234"}, {}};
    auto gpsPoint7 = PositionDateTimeData{Positions::OscherslebenSector1Point3, Timestamp{"15:06:12.234"}, {}};
    auto gpsPoint8 = PositionDateTimeData{Positions::OscherslebenSector1Point4, Timestamp{"15:06:13.234"}, {}};

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);

    REQUIRE(sectorFinishedEmitted == true);

    // Position to finish the lap
    auto gpsPoint9 = PositionDateTimeData{Positions::OscherslebenStartFinishLine1, {}, {}};
    auto gpsPoint10 = PositionDateTimeData{Positions::OscherslebenStartFinishLine2, {}, {}};
    auto gpsPoint11 = PositionDateTimeData{Positions::OscherslebenStartFinishLine3, {}, {}};
    auto gpsPoint12 = PositionDateTimeData{Positions::OscherslebenStartFinishLine4, {}, {}};

    lapTimer.updatePositionAndTime(gpsPoint9);
    lapTimer.updatePositionAndTime(gpsPoint10);
    lapTimer.updatePositionAndTime(gpsPoint11);
    lapTimer.updatePositionAndTime(gpsPoint12);

    REQUIRE(lapFinishedEmitted == true);
    REQUIRE(lapStartedEmitted == true);

    lapStartedEmitted = false;
    lapFinishedEmitted = false;
    sectorFinishedEmitted = false;

    lapTimer.updatePositionAndTime(gpsPoint5);
    lapTimer.updatePositionAndTime(gpsPoint6);
    lapTimer.updatePositionAndTime(gpsPoint7);
    lapTimer.updatePositionAndTime(gpsPoint8);
    REQUIRE(sectorFinishedEmitted == true);

    lapTimer.updatePositionAndTime(gpsPoint9);
    lapTimer.updatePositionAndTime(gpsPoint10);
    lapTimer.updatePositionAndTime(gpsPoint11);
    lapTimer.updatePositionAndTime(gpsPoint12);

    REQUIRE(lapFinishedEmitted == true);
    REQUIRE(lapStartedEmitted == true);
}

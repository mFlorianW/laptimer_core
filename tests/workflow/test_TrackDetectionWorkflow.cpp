#define CATCH_CONFIG_MAIN
#include "PositionDateTimeProvider.hpp"
#include "Positions.hpp"
#include "TrackDetection.hpp"
#include "TrackDetectionWorkflow.hpp"
#include "Tracks.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Workflow;
using namespace LaptimerCore::Algorithm;
using namespace LaptimerCore::TestHelper;

TEST_CASE("TrackDetectionWorkflow shall emit 'trackDetected' when successful detected a track.")
{
    auto trackDetector = TrackDetection{500};
    auto posInfoProvider = PositionDateTimeProvider{};
    auto tdw = TrackDetectionWorkflow{trackDetector, posInfoProvider};
    bool trackDetectedEmitted{false};

    tdw.trackDetected.connect([&] {
        trackDetectedEmitted = true;
    });
    tdw.setTracks({Tracks::getOscherslebenTrack()});
    tdw.startDetection();

    posInfoProvider.positionTimeData.set({{Positions::getOscherslebenPositionCamp()}, {}, {}});

    REQUIRE(trackDetectedEmitted == true);
}

TEST_CASE("TrackDetectionWorkflow shall return the TrackData when successful detected a track.")
{
    auto trackDetector = TrackDetection{500};
    auto posInfoProvider = PositionDateTimeProvider{};
    auto tdw = TrackDetectionWorkflow{trackDetector, posInfoProvider};

    tdw.setTracks({Tracks::getOscherslebenTrack()});
    tdw.startDetection();

    posInfoProvider.positionTimeData.set({{Positions::getOscherslebenPositionCamp()}, {}, {}});

    REQUIRE(tdw.getDetectedTrack() == Tracks::getOscherslebenTrack());
}

TEST_CASE("TrackDetectionWorkflow shall not emit 'trackDetected' when stopped.")
{
    auto trackDetector = TrackDetection{500};
    auto posInfoProvider = PositionDateTimeProvider{};
    auto tdw = TrackDetectionWorkflow{trackDetector, posInfoProvider};
    bool trackDetectedEmitted{false};

    tdw.trackDetected.connect([&] {
        trackDetectedEmitted = true;
    });
    tdw.setTracks({Tracks::getOscherslebenTrack()});

    tdw.startDetection();
    posInfoProvider.positionTimeData.set({{Positions::getOscherslebenPositionCamp()}, {}, {}});

    REQUIRE(trackDetectedEmitted == true);

    trackDetectedEmitted = false;
    tdw.stopDetection();
    posInfoProvider.positionTimeData.set({{Positions::getOscherslebenPositionCamp()}, {}, {}});

    REQUIRE(trackDetectedEmitted == false);
}

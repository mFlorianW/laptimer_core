#define CATCH_CONFIG_MAIN
#include "PositionInformationProvider.hpp"
#include "Positions.hpp"
#include "TrackDetection.hpp"
#include "TrackDetectionWorkflow.hpp"
#include "Tracks.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Workflow;
using namespace LaptimerCore::Algorithm;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("TrackDetectionWorkflow shall emit 'trackDetected' when successful detected a track.")
{
    Tracks::init();
    Positions::init();
    auto trackDetector = TrackDetection{500};
    auto posInfoProvider = PositionInformationProvider{};
    auto tdw = TrackDetectionWorkflow{trackDetector, posInfoProvider};
    bool trackDetectedEmitted{false};

    tdw.trackDetected.connect([&] { trackDetectedEmitted = true; });
    tdw.setTracks({Tracks::OscherslebenTrack});
    tdw.startDetection();

    posInfoProvider.setPositionData(Positions::OscherslebenPosition);

    REQUIRE(trackDetectedEmitted == true);
}

TEST_CASE("TrackDetectionWorkflow shall return the TrackData when successful detected a track.")
{
    Tracks::init();
    Positions::init();
    auto trackDetector = TrackDetection{500};
    auto posInfoProvider = PositionInformationProvider{};
    auto tdw = TrackDetectionWorkflow{trackDetector, posInfoProvider};

    tdw.setTracks({Tracks::OscherslebenTrack});
    tdw.startDetection();

    posInfoProvider.setPositionData(Positions::OscherslebenPosition);

    REQUIRE(tdw.getDetectedTrack() == Tracks::OscherslebenTrack);
}

TEST_CASE("TrackDetectionWorkflow shall not emit 'trackDetected' when stopped.")
{
    Tracks::init();
    Positions::init();
    auto trackDetector = TrackDetection{500};
    auto posInfoProvider = PositionInformationProvider{};
    auto tdw = TrackDetectionWorkflow{trackDetector, posInfoProvider};
    bool trackDetectedEmitted{false};

    tdw.trackDetected.connect([&] { trackDetectedEmitted = true; });
    tdw.setTracks({Tracks::OscherslebenTrack});

    tdw.startDetection();
    posInfoProvider.setPositionData(Positions::OscherslebenPosition);

    REQUIRE(trackDetectedEmitted == true);

    trackDetectedEmitted = false;
    tdw.stopDetection();
    posInfoProvider.setPositionData(Positions::OscherslebenPosition);

    REQUIRE(trackDetectedEmitted == false);
}

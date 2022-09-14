#include "ActiveSessionModel.hpp"

#include "TrackData.hpp"

using namespace LaptimerCore::Common;

ActiveSessionModel::ActiveSessionModel(LaptimerCore::Workflow::ITrackDetectionWorkflow &trackDetector,
                                       LaptimerCore::Workflow::IActiveSessionWorkflow &activeWorkSessionFlow)
    : mTrackDetector{trackDetector}
    , mActiveWorkSessionFlow{activeWorkSessionFlow}
{
    TrackData zuhauseTrack;
    zuhauseTrack.setTrackName("Flo Zuhause");
    PositionData finishline;
    finishline.setLatitude(52.25575);
    finishline.setLongitude(8.001452);

    zuhauseTrack.setFinishline(finishline);

    mTrackDetector.setTracks({zuhauseTrack});
    mTrackDetector.startDetection();

    mTrackDetector.trackDetected.connect([=] {
        detectedTrack = mTrackDetector.getDetectedTrack();
        mTrackDetector.stopDetection();
    });
}

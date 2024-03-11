#include "TrackDetectionWorkflow.hpp"

namespace LaptimerCore::Workflow
{
TrackDetectionWorkflow::TrackDetectionWorkflow(Algorithm::ITrackDetection& trackDetector,
                                               Positioning::IPositionDateTimeProvider& positionInfomationProvider)
    : ITrackDetectionWorkflow{}
    , mTrackDetector{trackDetector}
    , mPositionInfoProvider{positionInfomationProvider}
{
}

TrackDetectionWorkflow::~TrackDetectionWorkflow() = default;

void TrackDetectionWorkflow::startDetection()
{
    mActive = true;
    mPositionInfoProvider.positionTimeData.valueChanged().connect(
        &TrackDetectionWorkflow::onPositionInformationReceived,
        this);
}

void TrackDetectionWorkflow::stopDetection()
{
    mActive = false;
}

void TrackDetectionWorkflow::setTracks(std::vector<Common::TrackData> const& trackData)
{
    mTracksToDetect = trackData;
}

Common::TrackData TrackDetectionWorkflow::getDetectedTrack() const
{
    return mDetectedTrack;
}

void TrackDetectionWorkflow::onPositionInformationReceived()
{
    if (!mActive) {
        return;
    }

    for (auto const& track : mTracksToDetect) {
        if (mTrackDetector.isOnTrack(track, mPositionInfoProvider.positionTimeData.get().getPosition())) {
            mDetectedTrack = track;
            trackDetected.emit();
            break;
        }
    }
}

} // namespace LaptimerCore::Workflow

#include "ActiveSessionModel.hpp"

#include "TrackData.hpp"

using namespace LaptimerCore::Common;

ActiveSessionModel::ActiveSessionModel(LaptimerCore::Workflow::ITrackDetectionWorkflow &trackDetector,
                                       LaptimerCore::Workflow::IActiveSessionWorkflow &activeWorkSessionFlow,
                                       LaptimerCore::TrackManagement::ITrackDatabase &trackDatabase)
    : mTrackDetector{trackDetector}
    , mActiveSessionWorkFlow{activeWorkSessionFlow}
    , mTrackDatabase{trackDatabase}
{
    const auto tracks = mTrackDatabase.getTracks();
    mTrackDetector.setTracks({tracks});
    mTrackDetector.startDetection();

    mTrackDetector.trackDetected.connect([this] {
        mTrackData = mTrackDetector.getDetectedTrack();
        mTrackDetector.stopDetection();
        trackDetected.emit();
    });

    // TODO: provide these as string so we the UI doesn't to do any formatting
    mActiveSessionWorkFlow.currentLaptime.valueChanged().connect(
        [=]() { currentLaptime.set(mActiveSessionWorkFlow.currentLaptime.get()); });

    // TODO: provide these as string so we the UI doesn't to do any formatting
    mActiveSessionWorkFlow.currentSectorTime.valueChanged().connect(
        [=]() { currentSectorTime.set(mActiveSessionWorkFlow.currentSectorTime.get()); });

    mActiveSessionWorkFlow.lapCount.valueChanged().connect(
        [=]() { lapCount.set(mActiveSessionWorkFlow.lapCount.get()); });

    mActiveSessionWorkFlow.lapFinished.connect([=]() { lapFinished.emit(); });
    mActiveSessionWorkFlow.sectorFinshed.connect([=]() { sectorFinished.emit(); });
}

std::string ActiveSessionModel::getLastLapTime() const noexcept
{
    if (mActiveSessionWorkFlow.lastLaptime.get().asString().empty())
    {
        return {"00:00:000"};
    }

    return mActiveSessionWorkFlow.lastLaptime.get().asString();
}

std::string ActiveSessionModel::getLastSector() const noexcept
{
    if (mActiveSessionWorkFlow.lastSectorTime.get().asString().empty())
    {
        return {"00:00:000"};
    }

    return mActiveSessionWorkFlow.lastSectorTime.get().asString();
}

void ActiveSessionModel::confirmTrackDetection(bool confirmed)
{
    // track is not confirmed by the user so we start the track detection again.
    if (!confirmed)
    {
        mTrackDetector.stopDetection();
        return;
    }

    mActiveSessionWorkFlow.setTrack(mTrackDetector.getDetectedTrack());
    mActiveSessionWorkFlow.startActiveSession();
}

TrackData ActiveSessionModel::getDetectedTrack() const noexcept
{
    return mTrackData;
}

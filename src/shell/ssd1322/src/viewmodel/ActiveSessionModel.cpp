#include "ActiveSessionModel.hpp"

#include "TrackData.hpp"

using namespace LaptimerCore::Common;

ActiveSessionModel::ActiveSessionModel(LaptimerCore::Workflow::ITrackDetectionWorkflow &trackDetector,
                                       LaptimerCore::Workflow::IActiveSessionWorkflow &activeWorkSessionFlow)
    : mTrackDetector{trackDetector}
    , mActiveSessionWorkFlow{activeWorkSessionFlow}
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

    // TODO: provide these as string so we the UI doesn't to do any formatting
    mActiveSessionWorkFlow.currentLaptime.valueChanged().connect(
        [=]() { currentLaptime.set(mActiveSessionWorkFlow.currentLaptime.get()); });

    // TODO: provide these as string so we the UI doesn't to do any formatting
    mActiveSessionWorkFlow.currentSectorTime.valueChanged().connect(
        [=]() { currentLaptime.set(mActiveSessionWorkFlow.currentLaptime.get()); });

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

    return convertTimeToString(mActiveSessionWorkFlow.lastLaptime.get());
}

std::string ActiveSessionModel::getLastSector() const noexcept
{
    if (mActiveSessionWorkFlow.lastSectorTime.get().asString().empty())
    {
        return {"00:00:000"};
    }

    return convertTimeToString(mActiveSessionWorkFlow.lastSectorTime.get());
}

void ActiveSessionModel::confirmTrackDetection(bool confirmed)
{
    // track is not confirmed by the user so we start the track detection again.
    if (!confirmed)
    {
        mTrackDetector.startDetection();
        return;
    }

    mActiveSessionWorkFlow.startActiveSession();
}

std::string ActiveSessionModel::convertTimeToString(const LaptimerCore::Common::Timestamp timeStamp)
{
    std::array<char, 25> buffer;
    std::snprintf(&buffer[0],
                  buffer.size(),
                  "%01d:%01d.%01d",
                  timeStamp.getMinute(),
                  timeStamp.getHour(),
                  timeStamp.getFractionalOfSecond());

    return {buffer[0]};
}
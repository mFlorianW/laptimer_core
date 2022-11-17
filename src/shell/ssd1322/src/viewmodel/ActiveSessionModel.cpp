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

    auto oschersleben = TrackData{};
    oschersleben.setTrackName("Oschersleben");
    oschersleben.setStartline(PositionData{52.0270889, 11.2803483});
    oschersleben.setFinishline(PositionData{52.0270889, 11.2803483});
    oschersleben.setSections({PositionData{52.0298205, 11.2741851}, PositionData{52.0299681, 11.2772076}});

    mTrackDetector.setTracks({zuhauseTrack, oschersleben});
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

std::string ActiveSessionModel::convertTimeToString(const LaptimerCore::Common::Timestamp timeStamp)
{
    std::array<char, 25> buffer = {0};
    std::snprintf(&buffer[0],
                  buffer.size(),
                  "%02d:%02d.%01d",
                  timeStamp.getMinute(),
                  timeStamp.getHour(),
                  timeStamp.getFractionalOfSecond());

    return {buffer[0]};
}

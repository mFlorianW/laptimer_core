#include "ActiveSessionWorkflow.hpp"

using namespace LaptimerCore::Common;

namespace LaptimerCore::Workflow
{

ActiveSessionWorkflow::ActiveSessionWorkflow(Positioning::IPositionDateTimeProvider& positionDateTimeProvider,
                                             Algorithm::ILaptimer& laptimer,
                                             Storage::ISessionDatabase& database)
    : mDateTimeProvider{positionDateTimeProvider}
    , mLaptimer{laptimer}
    , mDatabase{database}
{
}

void ActiveSessionWorkflow::startActiveSession() noexcept
{
    mLaptimer.lapFinished.connect(&ActiveSessionWorkflow::onLapFinished, this);
    mLaptimer.sectorFinished.connect(&ActiveSessionWorkflow::onSectorFinished, this);
    mLaptimer.currentLaptime.valueChanged().connect(&ActiveSessionWorkflow::onCurrentLaptimeChanged, this);
    mLaptimer.currentSectorTime.valueChanged().connect(&ActiveSessionWorkflow::onCurrentSectorTimeChanged, this);
    mLaptimer.setTrack(mTrack);

    mPositionDateTimeUpdateHandle = mDateTimeProvider.positionTimeData.valueChanged().connect([=]() {
        mLaptimer.updatePositionAndTime(mDateTimeProvider.positionTimeData.get());
    });

    auto dateTime = mDateTimeProvider.positionTimeData.get();
    mSession = Common::SessionData{mTrack, dateTime.getDate(), dateTime.getTime()};
    lapCount.set(0);
}

void ActiveSessionWorkflow::stopActiveSession() noexcept
{
    mDateTimeProvider.positionTimeData.valueChanged().disconnect(mPositionDateTimeUpdateHandle);

    mSession = std::nullopt;
}

void ActiveSessionWorkflow::setTrack(Common::TrackData const& track) noexcept
{
    mTrack = track;
}

std::optional<Common::SessionData> ActiveSessionWorkflow::getSession() const noexcept
{
    return mSession;
}

void LaptimerCore::Workflow::ActiveSessionWorkflow::addSectorTime()
{
    auto const sectorTime = mLaptimer.getLastSectorTime();
    lastSectorTime.set(sectorTime);
    mCurrentLap.addSectorTime(sectorTime);
}

void ActiveSessionWorkflow::onLapFinished()
{
    // Session not started immediately return.
    if (!mSession) {
        return;
    }

    addSectorTime();

    mSession->addLap(mCurrentLap);
    mDatabase.storeSession(mSession.value());
    lastLaptime.set(mCurrentLap.getLaptime());
    mCurrentLap = Common::LapData{};

    auto const newLapCount = lapCount.get() + 1;
    lapCount.set(newLapCount);
    lapFinished.emit();
}

void ActiveSessionWorkflow::onSectorFinished()
{
    addSectorTime();
    sectorFinshed.emit();
}

void ActiveSessionWorkflow::onCurrentLaptimeChanged()
{
    currentLaptime.set(mLaptimer.currentLaptime.get());
}

void ActiveSessionWorkflow::onCurrentSectorTimeChanged()
{
    currentSectorTime.set(mLaptimer.currentSectorTime.get());
}

} // namespace LaptimerCore::Workflow

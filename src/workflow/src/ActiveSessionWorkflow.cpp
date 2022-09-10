#include "ActiveSessionWorkflow.hpp"

namespace LaptimerCore::Workflow
{

ActiveSessionWorkflow::ActiveSessionWorkflow(Positioning::IPositionDateTimeProvider &positionDateTimeProvider,
                                             Algorithm::ILaptimer &laptimer,
                                             Session::ISessionDatabase &database)
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

    auto dateTime = mDateTimeProvider.positionTimeData.get();
    mSession = Common::SessionData{mTrack, dateTime.getDate(), dateTime.getTime()};
    lapCount.set(0);
}

void ActiveSessionWorkflow::stopActiveSession() noexcept
{
    mSession = std::nullopt;
}

void ActiveSessionWorkflow::setTrack(const Common::TrackData &track) noexcept
{
    mTrack = track;
}

std::optional<Common::SessionData> ActiveSessionWorkflow::getSession() const noexcept
{
    return mSession;
}

void ActiveSessionWorkflow::onLapFinished()
{
    // Session not started immediately return.
    if (!mSession)
    {
        return;
    }

    mSession->addLap(mCurrentLap);
    mDatabase.storeSession(mSession.value());
    lastLaptime.set(mCurrentLap.getLaptime());

    const auto newLapCount = lapCount.get() + 1;
    lapCount.set(newLapCount);
}

void ActiveSessionWorkflow::onSectorFinished()
{
    const auto sectorTime = mLaptimer.getLastSectorTime();
    lastSectorTime.set(sectorTime);
    mCurrentLap.addSectorTime(sectorTime);
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

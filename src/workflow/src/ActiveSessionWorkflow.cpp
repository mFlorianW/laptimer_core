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

    auto dateTime = mDateTimeProvider.positionTimeData.get();
    mSession = Common::SessionData{mTrack, dateTime.getDate(), dateTime.getTime()};
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

    auto lap = Common::LapData{mLaptimer.getLastLaptime()};
    mSession->addLap(lap);
    mDatabase.storeSession(mSession.value());
    lastLaptime.set(lap.getLaptime());
}

void ActiveSessionWorkflow::onSectorFinished()
{
    lastSectorTime.set(mLaptimer.getLastSectorTime());
}

} // namespace LaptimerCore::Workflow

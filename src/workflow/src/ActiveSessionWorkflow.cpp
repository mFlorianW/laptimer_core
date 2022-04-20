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
    mLaptimer.lapFinished.connect(&ActiveSessionWorkflow::onLapFinished, this);
}

void ActiveSessionWorkflow::startActiveSession() noexcept
{
    auto dateTime = mDateTimeProvider.positionTimeData.get();
    mSession = Common::SessionData{mTrack, dateTime.getDate(), dateTime.getTime()};
}

void ActiveSessionWorkflow::stopActiveSession() noexcept
{
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

    auto lap = Common::LapData{};
    mSession->addLap(lap);
    mDatabase.storeSession(mSession.value());
}

} // namespace LaptimerCore::Workflow

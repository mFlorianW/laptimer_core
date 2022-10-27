#include "SessionViewModel.hpp"
#include <sstream>

SessionViewModel::SessionViewModel(LaptimerCore::Session::ISessionDatabase &sessionDb)
    : MenuEntry()
    , NavigatableModel{0}
    , mSessionDb{sessionDb}
{
    if (mSessionDb.getSessionCount() == 0)
    {
        return;
    }

    // set the initial property values
    setSize(mSessionDb.getSessionCount());
    displaySession(mSessionDb.getSessionCount() - 1);
}

SessionViewModel::~SessionViewModel() = default;

void SessionViewModel::handleNavigationUp()
{
    incrementIndex();
    displaySession(getIndex());
}

void SessionViewModel::handleNavigationDown()
{
    decrementIndex();
    displaySession(getIndex());
}

void SessionViewModel::displaySession(std::size_t index)
{
    const auto session = mSessionDb.getSessionByIndex(index);
    if (!session.has_value())
    {
        return;
    }

    sessionIndicator.set(std::to_string(index + 1) + "/" + std::to_string(mSessionDb.getSessionCount()));
    trackName.set(session->getTrack().getTrackName());
    date.set(session->getSessionDate().asString());
    time.set(session->getSessionTime().asString());
    laps.set(std::to_string(session->getNumberOfLaps()));
    bestlap.set(session->getLaps().at(0).getLaptime().asString());
}

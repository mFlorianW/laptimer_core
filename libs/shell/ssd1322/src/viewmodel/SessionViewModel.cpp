// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SessionViewModel.hpp"
#include <sstream>

SessionViewModel::SessionViewModel(LaptimerCore::Storage::ISessionDatabase& sessionDb)
    : MenuEntry()
    , NavigatableModel{0}
    , mSessionDb{sessionDb}
    , mLapView{mLapModel}
    , mLapViewCloseCommand(*this)
{
    mSessionDb.sessionAdded.connect(&SessionViewModel::onSessionAdded, this);
    mSessionDb.sessionUpdated.connect(&SessionViewModel::onSessionUpdated, this);
    mLapView.setCloseCommand(&mLapViewCloseCommand);

    // display initial session
    if (mSessionDb.getSessionCount() != 0) {
        setSize(mSessionDb.getSessionCount());
        displaySession(mSessionDb.getSessionCount() - 1);
    }
}

SessionViewModel::~SessionViewModel() = default;

void SessionViewModel::handleNavigationUp()
{
    decrementIndex();
    displaySession(getSize() - getIndex() - 1);
}

void SessionViewModel::handleNavigationDown()
{
    incrementIndex();
    displaySession(getSize() - getIndex() - 1);
}

void SessionViewModel::open()
{
    mActiveView = &mLapView;
    viewChanged.emit();
}

void SessionViewModel::close()
{
    mActiveView = mEntryView;
    viewChanged.emit();
}

void SessionViewModel::displaySession(std::size_t index)
{
    auto const session = mSessionDb.getSessionByIndex(index);
    if (!session.has_value()) {
        return;
    }

    mLapModel.setSessionData(session.value());
    sessionIndicator.set(std::to_string(index + 1) + "/" + std::to_string(mSessionDb.getSessionCount()));
    trackName.set(session->getTrack().getTrackName());
    date.set(session->getSessionDate().asString());
    time.set(session->getSessionTime().asString());
    laps.set(std::to_string(session->getNumberOfLaps()));
    bestlap.set(session->getLaps().at(0).getLaptime().asString());
}

void SessionViewModel::onSessionAdded()
{
    auto const oldIndex = getIndex();
    setSize(mSessionDb.getSessionCount());

    // If the view is on the top off all session we have to switch to the new session
    // and if the view is not on the top position we just stay at that position.
    if (oldIndex == 0) {
        displaySession(mSessionDb.getSessionCount() - 1);
    }
}

void SessionViewModel::onSessionUpdated(std::size_t index)
{
    // The ordering of the session in the oppsite to the index of the elements in the view
    // index = 0 is equal session index = max. That the reason for subtraction. If
    // the index is the same then session is displayed to the user and must be updated.
    if (index == (getSize() - 1) - getIndex()) {
        displaySession(index);
    }
}

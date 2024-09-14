// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "SessionEndpoint.hpp"
#include <ActiveSessionWorkflow.hpp>
#include <IPositionDateTimeProvider.hpp>
#include <ISessionDatabase.hpp>
#include <ITrackDatabase.hpp>
#include <RestServer.hpp>
#include <SimpleLaptimer.hpp>
#include <TrackDetection.hpp>
#include <TrackDetectionWorkflow.hpp>

namespace LaptimerCore::LappyHeadless
{

class LappyHeadless
{
public:
    LappyHeadless(LaptimerCore::Positioning::IPositionDateTimeProvider& posProvider,
                  LaptimerCore::Storage::ISessionDatabase& sessionDatabase,
                  LaptimerCore::Storage::ITrackDatabase& trackDatabase);

private:
    LaptimerCore::Positioning::IPositionDateTimeProvider& mPositionProvider;
    LaptimerCore::Storage::ISessionDatabase& mSessionDatabase;
    LaptimerCore::Storage::ITrackDatabase& mTrackDatabase;
    LaptimerCore::Algorithm::TrackDetection mTrackDetection{500};
    LaptimerCore::Workflow::TrackDetectionWorkflow mTrackDetectionWorkflow{mTrackDetection, mPositionProvider};
    LaptimerCore::Algorithm::SimpleLaptimer mSimpleLaptimer{};
    LaptimerCore::Workflow::ActiveSessionWorkflow mActiveSessionWorkflow{mPositionProvider,
                                                                         mSimpleLaptimer,
                                                                         mSessionDatabase};
    LaptimerCore::Rest::SessionEndpoint mSessionEndpoint{mSessionDatabase};
    LaptimerCore::Rest::RestServer mRestServer;
};

} // namespace LaptimerCore::LappyHeadless

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ActiveSessionModel.hpp"
#include "ActiveSessionView.hpp"
#include "ShowMenuScreenCommand.hpp"
#include <ActiveSessionWorkflow.hpp>
#include <IPositionDateTimeProvider.hpp>
#include <SimpleLaptimer.hpp>
#include <TrackDetection.hpp>
#include <TrackDetectionWorkflow.hpp>

class ScreenModel;
class MainScreenModel
{
public:
    MainScreenModel(ScreenModel& screenModel,
                    LaptimerCore::Positioning::IPositionDateTimeProvider& posDateTimeProvider,
                    LaptimerCore::Storage::ISessionDatabase& sessionDatabase,
                    LaptimerCore::Storage::ITrackDatabase& trackDatabase);
    View& getActiveView();

private:
    // Backends
    LaptimerCore::Algorithm::TrackDetection mTrackDetector{500};
    LaptimerCore::Algorithm::SimpleLaptimer mLapTimer;

    // ActiveSessionBackend
    LaptimerCore::Workflow::ActiveSessionWorkflow mActiveSessionWorkflow;

    // Models
    ScreenModel& mScreenModel;
    LaptimerCore::Workflow::TrackDetectionWorkflow mTrackDetectionWorkflow;
    ActiveSessionModel mActiveSessionModel;

    // Commands
    ShowMenuScreenCommand mShowMenuScreenCommand;

    // Views
    ActiveSessionView mActiveSessionView;
};

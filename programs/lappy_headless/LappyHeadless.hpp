// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <IPositionDateTimeProvider.hpp>
#include <ISessionDatabase.hpp>
#include <ITrackDatabase.hpp>
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
};

} // namespace LaptimerCore::LappyHeadless
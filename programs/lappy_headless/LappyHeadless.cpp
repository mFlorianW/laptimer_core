// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LappyHeadless.hpp"

namespace LaptimerCore::LappyHeadless
{

LappyHeadless::LappyHeadless(LaptimerCore::Positioning::IPositionDateTimeProvider& posProvider,
                             LaptimerCore::Storage::ISessionDatabase& sessionDatabase,
                             LaptimerCore::Storage::ITrackDatabase& trackDatabase)
    : mPositionProvider{posProvider}
    , mSessionDatabase{sessionDatabase}
    , mTrackDatabase{trackDatabase}
{
    mTrackDetectionWorkflow.trackDetected.connect([this] {
        auto const track = mTrackDetectionWorkflow.getDetectedTrack();
        std::cout << "Track detected:" << track.getTrackName() << "\n";
        mTrackDetectionWorkflow.stopDetection();
        mActiveSessionWorkflow.setTrack(track);
        mActiveSessionWorkflow.startActiveSession();
    });

    mActiveSessionWorkflow.lapFinished.connect([this] {
        std::cout << "Lap" << mActiveSessionWorkflow.lapCount.get()
                  << " finished:" << mActiveSessionWorkflow.lastLaptime.get().asString() << "\n";
    });

    mTrackDetectionWorkflow.setTracks(mTrackDatabase.getTracks());
    mTrackDetectionWorkflow.startDetection();
}

} // namespace LaptimerCore::LappyHeadless

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __ITRACKDETECTIONWORKFLOW__H__
#define __ITRACKDETECTIONWORKFLOW__H__

#include "TrackData.hpp"
#include "kdbindings/signal.h"

namespace LaptimerCore::Workflow
{

/**
 * The ITrackDetectionWorkflow defines the interface for conrolling the
 * process of a track detection.
 */
class ITrackDetectionWorkflow
{
public:
    /**
     * Default destructor
     */
    virtual ~ITrackDetectionWorkflow() = default;

    /**
     * Starts the track detection.
     */
    virtual void startDetection() = 0;

    /**
     * Stop the track detection.
     */
    virtual void stopDetection() = 0;

    /**
     * Sets a list that shall be used for the track detection.
     * @param trackDatas A list of tracks which is used during the track detection.
     */
    virtual void setTracks(std::vector<Common::TrackData> const& trackData) = 0;

    /**
     * Gives the detected Track.
     * This value is only valid after receiving the track detected signal.
     * @return TrackData The detected track.
     */
    virtual Common::TrackData getDetectedTrack() const = 0;

    /**
     * This signal is emitted when a track is detected.
     */
    KDBindings::Signal<> trackDetected;

protected:
    ITrackDetectionWorkflow() = default;
};

} // namespace LaptimerCore::Workflow

#endif //!__ITRACKDETECTIONWORKFLOW__H__
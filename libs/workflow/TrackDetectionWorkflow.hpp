// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __TRACKDETECTIONWORKFLOW__H__
#define __TRACKDETECTIONWORKFLOW__H__

#include "ITrackDetectionWorkflow.hpp"
#include <IPositionDateTimeProvider.hpp>
#include <ITrackDetection.hpp>

namespace LaptimerCore::Workflow
{

class TrackDetectionWorkflow : public ITrackDetectionWorkflow
{
public:
    /**
     * Constructs a TrackDetectionWorkflow.
     * The class doesn't take the ownership of the passed arguments.
     * So the caller must guarantee that all objects live as long as this class.
     * @param trackDetector The algorithm that shall be used for the track detection.
     * @param positionInfomationProvider The position information provider that shall be used for the track detection.
     */
    TrackDetectionWorkflow(Algorithm::ITrackDetection& trackDetector,
                           Positioning::IPositionDateTimeProvider& positionInfomationProvider);

    ~TrackDetectionWorkflow();

    /**
     * @copydoc ITrackDetectionWorkflow::startDetection()
     */
    void startDetection() override;

    /**
     * @copydoc ITrackDetectionWorkflow::stopDetection()
     */
    void stopDetection() override;

    /**
     * @copydoc ITrackDetectionWorkflow::setTracks(const std::vector<TrackData> &trackData)
     */
    void setTracks(std::vector<Common::TrackData> const& trackData) override;

    /**
     * @copydoc ITrackDetectionWorkflow::getDetectedTrack()
     */
    Common::TrackData getDetectedTrack() const override;

private:
    void onPositionInformationReceived();

private:
    bool mActive{false};
    Common::TrackData mDetectedTrack;
    std::vector<Common::TrackData> mTracksToDetect;
    Algorithm::ITrackDetection& mTrackDetector;
    Positioning::IPositionDateTimeProvider& mPositionInfoProvider;
};

} // namespace LaptimerCore::Workflow
#endif //!__TRACKDETECTIONWORKFLOW__H__

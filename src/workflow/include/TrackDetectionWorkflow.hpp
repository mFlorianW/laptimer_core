#ifndef __TRACKDETECTIONWORKFLOW__H__
#define __TRACKDETECTIONWORKFLOW__H__

#include "IPositionInformationProvider.hpp"
#include "ITrackDetection.hpp"
#include "ITrackDetectionWorkflow.hpp"

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
    TrackDetectionWorkflow(Algorithm::ITrackDetection &trackDetector,
                           Positioning::IPositionInformationProvider &positionInfomationProvider);

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
    void setTracks(const std::vector<Common::TrackData> &trackData) override;

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
    Algorithm::ITrackDetection &mTrackDetector;
    Positioning::IPositionInformationProvider &mPositionInfoProvider;
};

} // namespace LaptimerCore::Workflow
#endif //!__TRACKDETECTIONWORKFLOW__H__

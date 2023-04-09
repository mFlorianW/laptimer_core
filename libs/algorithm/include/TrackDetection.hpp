#ifndef __CIRCLETRACKDETECTION__H__
#define __CIRCLETRACKDETECTION__H__

#include "ITrackDetection.hpp"
#include <cstdint>

namespace LaptimerCore::Algorithm
{

class TrackDetection : public ITrackDetection
{
public:
    /**
     * Constructs a TrackDetection within the given radius.
     * @param detectRadiusInMeter The radius that shall be used during the detection.
     */
    TrackDetection(std::uint16_t detectRadiusInMeter);

    /**
     * @copydoc ITrackDataDetection::isOnTrack()
     */
    bool isOnTrack(const Common::TrackData &track, const Common::PositionData &position) const override;

private:
    std::uint16_t mDetectionRadius;
};

} // namespace LaptimerCore::Algorithm

#endif //!__CIRCLETRACKDETECTION__H__
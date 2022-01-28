#ifndef __TRACKDETECTION__H__
#define __TRACKDETECTION__H__

#include "ITrackDetection.hpp"

namespace LaptimerCore::Algorithm
{

class TrackDetection : public ITrackDetection
{
public:
    /**
     * @copydoc ITrackDataDetection::isOnTrack()
     */
    bool isOnTrack(const Common::TrackData &track, const Common::PositionData &position) const override;
};

} // namespace LaptimerCore::Algorithm

#endif //!__TRACKDETECTION__H__
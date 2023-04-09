#ifndef __ITRACKDETECTION__H__
#define __ITRACKDETECTION__H__

#include <PositionData.hpp>
#include <TrackData.hpp>

namespace LaptimerCore::Algorithm
{

class ITrackDetection
{
public:
    virtual ~ITrackDetection() = default;

    /**
     * Checks if the given position is on the given track.
     * @param track The track to test if the position is on that track.
     * @param position The given position that shall be used for the check.
     * @return true The position is on the track.
     * @return false The position is not on the track.
     */
    virtual bool isOnTrack(const Common::TrackData &track, const Common::PositionData &position) const = 0;
};

} // namespace LaptimerCore::Algorithm

#endif //!__ITRACKDETECTION__H__
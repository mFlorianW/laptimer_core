#include "TrackDetection.hpp"
#include "DistanceCalculator.hpp"
#include <cmath>

using namespace LaptimerCore::Common;

namespace LaptimerCore::Algorithm
{

TrackDetection::TrackDetection(std::uint16_t detectRadiusInMeter)
    : mDetectionRadius(detectRadiusInMeter)
{
}

bool TrackDetection::isOnTrack(TrackData const& track, PositionData const& position) const
{
    auto distance = static_cast<std::uint16_t>(DistanceCalculator::calculateDistance(track.getFinishline(), position));
    return distance <= mDetectionRadius;
}

} // namespace LaptimerCore::Algorithm
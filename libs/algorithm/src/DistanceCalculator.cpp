#include "DistanceCalculator.hpp"
#include <cmath>

namespace LaptimerCore::Algorithm::DistanceCalculator
{

float calculateDistance(const Common::PositionData &pos1, const Common::PositionData &pos2)
{
    float lat = (pos1.getLatitude() + pos2.getLatitude()) / 2 * 0.01745f;
    float dx = 111300 * cos(lat) * (pos1.getLongitude() - pos2.getLongitude());
    float dy = 111300 * (pos1.getLatitude() - pos2.getLatitude());
    float distance = sqrt(dx * dx + dy * dy);

    return distance;
}

}; // namespace LaptimerCore::Algorithm::DistanceCalculator
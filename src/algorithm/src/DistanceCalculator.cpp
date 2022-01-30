#include "DistanceCalculator.hpp"
#include <cmath>

namespace LaptimerCore::Algorithm::DistanceCalculator
{

float calculateDistance(const Common::PositionData &pos1, const Common::PositionData &pos2)
{
    float lat = (pos1.latitude + pos2.latitude) / 2 * 0.01745f;
    float dx = 111300 * cos(lat) * (pos1.longitude - pos2.longitude);
    float dy = 111300 * (pos1.latitude - pos2.latitude);
    float distance = sqrt(dx * dx + dy * dy);

    return distance;
}

}; // namespace LaptimerCore::Algorithm::DistanceCalculator
#include "Laptimer.hpp"
#include <numeric>

namespace LaptimerCore::TestHelper
{
Laptimer::Laptimer()
{
}

void Laptimer::setTrack(const Common::TrackData &track)
{
}

void Laptimer::updatePositionAndTime(const Common::PositionDateTimeData &data)
{
    lastPostionDateTime = data;
}

Common::Timestamp Laptimer::getLastLaptime() const
{
    return std::accumulate(sectorTimes.cbegin(), sectorTimes.cend(), Common::Timestamp{});
}

Common::Timestamp Laptimer::getLastSectorTime() const
{
    if (sectorTimes.empty())
    {
        return Common::Timestamp{};
    }
    return sectorTimes.back();
}

} // namespace LaptimerCore::TestHelper
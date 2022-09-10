#include "Laptimer.hpp"
#include <numeric>

namespace LaptimerCore::Test::Dummy
{
Laptimer::Laptimer()
{
}

void Laptimer::setTrack(const Common::TrackData &track)
{
}

void Laptimer::updatePositionAndTime(const Common::PositionDateTimeData &data)
{
}

Common::Timestamp Laptimer::getLastLaptime() const
{
    return std::accumulate(sectorTimes.cbegin(), sectorTimes.cend(), Common::Timestamp{});
}

Common::Timestamp Laptimer::getLastSectorTime() const
{
    return sectorTimes.back();
}

} // namespace LaptimerCore::Test::Dummy

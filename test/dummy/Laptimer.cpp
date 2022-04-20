#include "Laptimer.hpp"

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
    return lastLapTime;
}

Common::Timestamp Laptimer::getLastSectorTime() const
{
    return lastSectorTime;
}

} // namespace LaptimerCore::Test::Dummy

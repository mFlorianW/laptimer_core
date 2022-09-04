#ifndef LAPTIMER_HPP
#define LAPTIMER_HPP

#include "ILaptimer.hpp"

namespace LaptimerCore::Test::Dummy
{

class Laptimer final : public Algorithm::ILaptimer
{
public:
    Laptimer();

    void setTrack(const Common::TrackData &track) override;

    void updatePositionAndTime(const Common::PositionDateTimeData &data) override;

    Common::Timestamp getLastLaptime() const override;

    Common::Timestamp getLastSectorTime() const override;

    Common::Timestamp lastSectorTime;
    Common::Timestamp lastLapTime;
};

} // namespace LaptimerCore::Test::Dummy

#endif // LAPTIMER_HPP
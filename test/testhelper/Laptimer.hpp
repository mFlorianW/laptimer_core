#ifndef LAPTIMER_HPP
#define LAPTIMER_HPP

#include "ILaptimer.hpp"

namespace LaptimerCore::TestHelper
{

class Laptimer final : public Algorithm::ILaptimer
{
public:
    Laptimer();

    void setTrack(const Common::TrackData &track) override;

    void updatePositionAndTime(const Common::PositionDateTimeData &data) override;

    Common::Timestamp getLastLaptime() const override;

    Common::Timestamp getLastSectorTime() const override;

    std::vector<Common::Timestamp> sectorTimes;

    Common::PositionDateTimeData lastPostionDateTime;
};

} // namespace LaptimerCore::TestHelper

#endif // LAPTIMER_HPP
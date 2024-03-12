// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef LAPTIMER_HPP
#define LAPTIMER_HPP

#include "ILaptimer.hpp"

namespace LaptimerCore::TestHelper
{

class Laptimer final : public Algorithm::ILaptimer
{
public:
    Laptimer();

    void setTrack(Common::TrackData const& track) override;

    void updatePositionAndTime(Common::PositionDateTimeData const& data) override;

    Common::Timestamp getLastLaptime() const override;

    Common::Timestamp getLastSectorTime() const override;

    std::vector<Common::Timestamp> sectorTimes;

    Common::PositionDateTimeData lastPostionDateTime;
};

} // namespace LaptimerCore::TestHelper

#endif // LAPTIMER_HPP

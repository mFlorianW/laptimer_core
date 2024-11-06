// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "Laptimer.hpp"
#include <numeric>

namespace Rapid::TestHelper
{
Laptimer::Laptimer()
{
}

void Laptimer::setTrack(Common::TrackData const& track)
{
}

void Laptimer::updatePositionAndTime(Common::PositionDateTimeData const& data)
{
    lastPostionDateTime = data;
}

Common::Timestamp Laptimer::getLastLaptime() const
{
    return std::accumulate(sectorTimes.cbegin(), sectorTimes.cend(), Common::Timestamp{});
}

Common::Timestamp Laptimer::getLastSectorTime() const
{
    if (sectorTimes.empty()) {
        return Common::Timestamp{};
    }
    return sectorTimes.back();
}

} // namespace Rapid::TestHelper

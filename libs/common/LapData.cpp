// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LapData.hpp"
#include <ArduinoJson.hpp>
#include <utility>

namespace Rapid::Common
{

class SharedLap : public SharedData
{
public:
    std::vector<Timestamp> mSectorTimes;

    friend bool operator==(SharedLap const& lhs, SharedLap const& rhs)
    {
        return (lhs.mSectorTimes) == (rhs.mSectorTimes);
    }
};

LapData::LapData()
    : mData{new SharedLap}
{
}

LapData::LapData(Timestamp const& laptime)
    : mData{new SharedLap}
{
    mData->mSectorTimes.push_back(laptime);
}

LapData::LapData(std::vector<Timestamp> const& sectorTimes)
    : mData{new SharedLap}
{
    mData->mSectorTimes = sectorTimes;
}

LapData::~LapData() = default;

LapData::LapData(LapData const& other) = default;

LapData& LapData::operator=(LapData const& other) = default;

LapData::LapData(LapData&& other) noexcept
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

LapData& LapData::operator=(LapData&& other) noexcept
{
    LapData moved{std::move(other)};
    std::swap(mData, moved.mData);
    return *this;
}

Timestamp LapData::getLaptime() const noexcept
{
    auto laptime = Timestamp{};
    for (auto const& sectorTime : std::as_const(getSectorTimes())) {
        laptime = laptime + sectorTime;
    }

    return laptime;
}

std::size_t LapData::getSectorTimeCount() const noexcept
{
    return mData->mSectorTimes.size();
}

std::optional<Timestamp> LapData::getSectorTime(std::size_t index) const noexcept
{
    if (index > mData->mSectorTimes.size()) {
        return std::nullopt;
    }

    return std::optional<Timestamp>{mData->mSectorTimes[index]};
}

std::vector<Timestamp> const& LapData::getSectorTimes() const noexcept
{
    return mData->mSectorTimes;
}

void LapData::addSectorTime(Timestamp const& sectorTime)
{
    mData->mSectorTimes.push_back(sectorTime);
}

void LapData::addSectorTimes(std::vector<Timestamp> const& sectorTimes)
{
    mData->mSectorTimes = sectorTimes;
}

bool operator==(LapData const& lhs, LapData const& rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(LapData const& lhs, LapData const& rhs)
{
    return !(lhs == rhs);
}

} // namespace Rapid::Common

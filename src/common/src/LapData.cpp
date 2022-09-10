#include "LapData.hpp"
#include <ArduinoJson.hpp>
#include <utility>

namespace LaptimerCore::Common
{

class SharedLap : public SharedData
{
public:
    std::vector<Timestamp> mSectorTimes;

    friend bool operator==(const SharedLap &lhs, const SharedLap &rhs)
    {
        return (lhs.mSectorTimes) == (rhs.mSectorTimes);
    }
};

LapData::LapData()
    : mData{new SharedLap}
{
}

LapData::LapData(const Timestamp &laptime)
    : mData{new SharedLap}
{
    mData->mSectorTimes.push_back(laptime);
}

LapData::LapData(const std::vector<Timestamp> &sectorTimes)
    : mData{new SharedLap}
{
    mData->mSectorTimes = sectorTimes;
}

LapData::~LapData() = default;

LapData::LapData(const LapData &other) = default;

LapData &LapData::operator=(const LapData &other) = default;

LapData::LapData(LapData &&other) noexcept
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

LapData &LapData::operator=(LapData &&other) noexcept
{
    LapData moved{std::move(other)};
    std::swap(mData, moved.mData);
    return *this;
}

Timestamp LapData::getLaptime() const noexcept
{
    auto laptime = Timestamp{};
    for (const auto &sectorTime : std::as_const(getSectorTimes()))
    {
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
    if (index > mData->mSectorTimes.size())
    {
        return std::nullopt;
    }

    return std::optional<Timestamp>{mData->mSectorTimes[index]};
}

const std::vector<Timestamp> &LapData::getSectorTimes() const noexcept
{
    return mData->mSectorTimes;
}

void LapData::addSectorTime(const Timestamp &sectorTime)
{
    mData->mSectorTimes.push_back(sectorTime);
}

void LapData::addSectorTimes(const std::vector<Timestamp> &sectorTimes)
{
    mData->mSectorTimes = sectorTimes;
}

bool operator==(const LapData &lhs, const LapData &rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(const LapData &lhs, const LapData &rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common

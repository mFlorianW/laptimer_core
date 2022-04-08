#include "LapData.hpp"
#include <ArduinoJson.hpp>

namespace LaptimerCore::Common
{

class SharedLap : public SharedData
{
public:
    Timestamp mLaptime;
    std::vector<Timestamp> mSectorTimes;

    friend bool operator==(const SharedLap &lhs, const SharedLap &rhs)
    {
        // clang-format off
        return ((lhs.mLaptime) == (rhs.mLaptime) &&
                (lhs.mSectorTimes) == (rhs.mSectorTimes));
        // clang-format on
    }
};

LapData::LapData()
    : mData{new SharedLap}
{
}

LapData::~LapData() = default;

LapData::LapData(const LapData &other)
    : mData(other.mData)
{
}

LapData &LapData::operator=(const LapData &other)
{
    mData = other.mData;
    return *this;
}

LapData::LapData(LapData &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

LapData &LapData::operator=(LapData &&other)
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

const std::optional<Timestamp> LapData::getSectorTime(std::size_t index) const noexcept
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

void LapData::addSectorTimes(const std::vector<Timestamp> sectorTimes)
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

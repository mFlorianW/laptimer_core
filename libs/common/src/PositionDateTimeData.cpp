#include "PositionDateTimeData.hpp"

namespace LaptimerCore::Common
{

class SharedPositionTimeData : public SharedData
{
public:
    PositionData mPosition;
    Timestamp mTime;
    Date mDate;

    friend bool operator==(const SharedPositionTimeData &lhs, const SharedPositionTimeData &rhs)
    {
        // clang-format off
        return ((lhs.mPosition) == (rhs.mPosition) &&
                (lhs.mTime) == (rhs.mTime) &&
                (lhs.mDate) == (rhs.mDate));
        // clang-format on
    }
};

PositionDateTimeData::PositionDateTimeData()
    : mData(new SharedPositionTimeData{})
{
}

PositionDateTimeData::PositionDateTimeData(const PositionData &posData, const Timestamp &time, const Date &date)
    : mData{new SharedPositionTimeData{}}
{
    mData->mPosition = posData;
    mData->mTime = time;
    mData->mDate = date;
}

PositionDateTimeData::~PositionDateTimeData() = default;

PositionDateTimeData::PositionDateTimeData(const PositionDateTimeData &other)
    : mData(other.mData)
{
}

PositionDateTimeData &PositionDateTimeData::operator=(const PositionDateTimeData &other)
{
    mData = other.mData;
    return *this;
}

PositionDateTimeData::PositionDateTimeData(PositionDateTimeData &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

PositionDateTimeData &PositionDateTimeData::operator=(PositionDateTimeData &&other)
{
    PositionDateTimeData moved{std::move(other)};
    std::swap(moved.mData, mData);
    return *this;
}

PositionData PositionDateTimeData::getPosition() const noexcept
{
    return mData->mPosition;
}

void PositionDateTimeData::setPosition(const PositionData &position)
{
    mData->mPosition = position;
}

Timestamp PositionDateTimeData::getTime() const noexcept
{
    return mData->mTime;
}

void PositionDateTimeData::setTime(const Timestamp &time)
{
    mData->mTime = time;
}

Date PositionDateTimeData::getDate() const noexcept
{
    return mData->mDate;
}

void PositionDateTimeData::setDate(const Date &date)
{
    mData->mDate = date;
}

bool operator==(const PositionDateTimeData &lhs, const PositionDateTimeData &rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(const PositionDateTimeData &lhs, const PositionDateTimeData &rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common

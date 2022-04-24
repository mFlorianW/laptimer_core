#include "PositionDateTimeData.hpp"

namespace LaptimerCore::Common
{

class SharedPositionDataTimeData : public SharedData
{
public:
    PositionData mPosition;
    Timestamp mTime;
    Date mDate;

    friend bool operator==(const SharedPositionDataTimeData &lhs, const SharedPositionDataTimeData &rhs)
    {
        // clang-format off
        return ((lhs.mPosition) == (rhs.mPosition) &&
                (lhs.mTime) == (rhs.mTime) &&
                (lhs.mDate) == (rhs.mDate));
        // clang-format on
    }
};

PositionDateTimeData::PositionDateTimeData()
    : mData(new SharedPositionDataTimeData{})
{
}

PositionDateTimeData::~PositionDateTimeData() = default;

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

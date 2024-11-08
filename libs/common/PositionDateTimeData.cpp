// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "PositionDateTimeData.hpp"

namespace Rapid::Common
{

class SharedPositionTimeData : public SharedData
{
public:
    PositionData mPosition;
    Timestamp mTime;
    Date mDate;

    friend bool operator==(SharedPositionTimeData const& lhs, SharedPositionTimeData const& rhs)
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

PositionDateTimeData::PositionDateTimeData(PositionData const& posData, Timestamp const& time, Date const& date)
    : mData{new SharedPositionTimeData{}}
{
    mData->mPosition = posData;
    mData->mTime = time;
    mData->mDate = date;
}

PositionDateTimeData::~PositionDateTimeData() = default;

PositionDateTimeData::PositionDateTimeData(PositionDateTimeData const& other) = default;
PositionDateTimeData& PositionDateTimeData::operator=(PositionDateTimeData const& other) = default;
PositionDateTimeData::PositionDateTimeData(PositionDateTimeData&& other) = default;

PositionDateTimeData& PositionDateTimeData::operator=(PositionDateTimeData&& other)
{
    PositionDateTimeData moved{std::move(other)};
    std::swap(moved.mData, mData);
    return *this;
}

PositionData PositionDateTimeData::getPosition() const noexcept
{
    return mData->mPosition;
}

void PositionDateTimeData::setPosition(PositionData const& position)
{
    mData->mPosition = position;
}

Timestamp PositionDateTimeData::getTime() const noexcept
{
    return mData->mTime;
}

void PositionDateTimeData::setTime(Timestamp const& time)
{
    mData->mTime = time;
}

Date PositionDateTimeData::getDate() const noexcept
{
    return mData->mDate;
}

void PositionDateTimeData::setDate(Date const& date)
{
    mData->mDate = date;
}

bool operator==(PositionDateTimeData const& lhs, PositionDateTimeData const& rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(PositionDateTimeData const& lhs, PositionDateTimeData const& rhs)
{
    return !(lhs == rhs);
}

} // namespace Rapid::Common

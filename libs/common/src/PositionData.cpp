#include "PositionData.hpp"
#include <cmath>
#include <limits>

namespace LaptimerCore::Common
{

class SharedPositionData : public SharedData
{
public:
    float latitude = 0.0f;
    float longitude = 0.0f;

    friend bool operator==(const SharedPositionData &lhs, const SharedPositionData &rhs)
    {
        // clang-format off
        return  ((std::fabs(lhs.latitude - rhs.latitude) < std::numeric_limits<float>::epsilon()) &&
                 (std::fabs(lhs.longitude - rhs.longitude) < std::numeric_limits<float>::epsilon()));
        // clang-format on
    }
};

PositionData::PositionData()
    : mData{new SharedPositionData{}}
{
}

PositionData::PositionData(float latitude, float longitude)
    : mData{new SharedPositionData{}}
{
    mData->latitude = latitude;
    mData->longitude = longitude;
}

PositionData::~PositionData() = default;

PositionData::PositionData(const PositionData &other)
    : mData(other.mData)
{
}

PositionData &PositionData::operator=(const PositionData &other)
{
    mData = other.mData;
    return *this;
}

PositionData::PositionData(PositionData &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

PositionData &PositionData::operator=(PositionData &&other)
{
    PositionData moved{std::move(other)};
    std::swap(moved.mData, mData);
    return *this;
}

float PositionData::getLatitude() const
{
    return mData->latitude;
}

void PositionData::setLatitude(float latitude)
{
    mData->latitude = latitude;
}

float PositionData::getLongitude() const
{
    return mData->longitude;
}

void PositionData::setLongitude(float longitude)
{
    mData->longitude = longitude;
}

bool operator==(const PositionData &lhs, const PositionData &rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(const PositionData &lhs, const PositionData &rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common
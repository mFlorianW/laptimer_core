#include "PositionData.hpp"

namespace LaptimerCore::Common
{

class SharedPositionData : public SharedData
{
public:
    float latitude = 0.0f;
    float longitude = 0.0f;
};

PositionData::PositionData()
    : mData{new SharedPositionData{}}
{
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

} // namespace LaptimerCore::Common

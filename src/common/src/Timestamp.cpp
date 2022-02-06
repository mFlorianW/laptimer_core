#include "Timestamp.hpp"

namespace LaptimerCore::Common
{
class SharedTimestamp : public SharedData
{
public:
    std::uint8_t hour;
    std::uint8_t minute;
    std::uint8_t second;
    std::uint16_t fractionalOfSecond;
};

Timestamp::Timestamp()
    : mData{new SharedTimestamp{}}
{
}

Timestamp::~Timestamp() = default;

Timestamp::Timestamp(const Timestamp &other)
    : mData{other.mData}
{
}

Timestamp &Timestamp::operator=(const Timestamp &other)
{
    mData = other.mData;
    return *this;
}

Timestamp::Timestamp(Timestamp &&other)
    : mData{std::move(other.mData)}
{
}

Timestamp &Timestamp::operator=(Timestamp &&other)
{
    Timestamp moved{std::move(other)};
    std::swap(moved.mData, mData);
    return *this;
}

std::uint8_t Timestamp::getHour() const
{
    return mData->hour;
}

void Timestamp::setHour(std::uint8_t hour)
{
    mData->hour = hour;
}

std::uint8_t Timestamp::getMinute() const
{
    return mData->minute;
}

void Timestamp::setMinute(std::uint8_t minute)
{
    mData->minute = minute;
}

std::uint8_t Timestamp::getSecond() const
{
    return mData->second;
}

void Timestamp::setSecond(std::uint8_t second)
{
    mData->second = second;
}

std::uint16_t Timestamp::getFractionalOfSecond() const
{
    return mData->fractionalOfSecond;
}

void Timestamp::setFractionalOfSecond(std::uint16_t fractionalOfSecond)
{
    mData->fractionalOfSecond = fractionalOfSecond;
}

} // namespace LaptimerCore::Common
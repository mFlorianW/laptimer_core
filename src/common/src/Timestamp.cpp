#include "Timestamp.hpp"
#include <iomanip>
#include <sstream>

namespace LaptimerCore::Common
{
class SharedTimestamp : public SharedData
{
public:
    std::uint8_t hour;
    std::uint8_t minute;
    std::uint8_t second;
    std::uint16_t fractionalOfSecond;

    friend bool operator==(const SharedTimestamp &lhs, const SharedTimestamp &rhs)
    {
        // clang-format off
        return ((lhs.hour) == (rhs.hour) &&
                (lhs.minute) == (rhs.minute) &&
                (lhs.second) == (rhs.second) &&
                (lhs.fractionalOfSecond) == (rhs.fractionalOfSecond));
        // clang-format on
    }
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

std::string Timestamp::asString() const noexcept
{
    std::ostringstream timeAsString;

    // clang-format off
    timeAsString << std::setw(2) << std::setfill('0') << std::to_string(getHour()) << ":"
                 << std::setw(2) << std::setfill('0') << std::to_string(getMinute()) << ":"
                 << std::setw(2) << std::setfill('0') << std::to_string(getSecond()) << "."
                 << std::setw(3) << std::setfill('0') << std::to_string(getFractionalOfSecond());
    // clang-format on

    return timeAsString.str();
}
Timestamp Timestamp::operator+(const Timestamp &rhs) const noexcept
{
    auto tempFractionalSecond = getFractionalOfSecond() + rhs.getFractionalOfSecond();
    std::uint8_t overflowSecond = 0;
    if (tempFractionalSecond >= 1000)
    {
        overflowSecond = 1;
        tempFractionalSecond -= 1000;
    }

    auto tempSecond = overflowSecond + getSecond() + rhs.getSecond();
    std::uint8_t overflowMinute = 0;
    if (tempSecond >= 60)
    {
        overflowMinute = 1;
        tempSecond -= 60;
    }

    auto tempMinute = overflowMinute + getMinute() + rhs.getMinute();
    std::uint8_t overflowHour = 0;
    if (tempMinute >= 60)
    {
        overflowHour = 1;
        tempMinute -= 60;
    }

    auto tempHour = overflowHour + getHour() + rhs.getHour();
    if (tempHour >= 24)
    {
        tempHour -= 24;
    }

    Timestamp ts;
    ts.setHour(tempHour);
    ts.setMinute(tempMinute);
    ts.setSecond(tempSecond);
    ts.setFractionalOfSecond(tempFractionalSecond);

    return ts;
}

Timestamp Timestamp::operator-(const Timestamp &rhs) const noexcept
{
    Timestamp result;
    auto tempHour = getHour() - rhs.getHour();
    if (tempHour < 0)
    {
        tempHour = 24 + tempHour;
    }

    auto tempMinute = getMinute() - rhs.getMinute();
    if (tempMinute < 0)
    {
        tempMinute = 60 + tempMinute;
    }

    auto tempSecond = getSecond() - rhs.getSecond();
    if (tempSecond < 0)
    {
        tempSecond = 60 + tempSecond;
    }
    auto tempFractionalOfSecond = getFractionalOfSecond() - rhs.getFractionalOfSecond();
    if (tempFractionalOfSecond < 0)
    {
        tempFractionalOfSecond = 1000 + tempFractionalOfSecond;
    }

    result.setHour(tempHour);
    result.setMinute(tempMinute);
    result.setSecond(tempSecond);
    result.setFractionalOfSecond(tempFractionalOfSecond);
    return result;
}

bool operator==(const Timestamp &lhs, const Timestamp &rhs)
{
    return lhs.mData == rhs.mData || *(lhs.mData) == *(rhs.mData);
}

bool operator!=(const Timestamp &lhs, const Timestamp &rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common

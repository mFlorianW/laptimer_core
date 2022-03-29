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
    Timestamp ts;
    ts.setHour(getHour() + rhs.getHour());
    ts.setMinute(getMinute() + rhs.getMinute());
    ts.setSecond(getSecond() + rhs.getSecond());
    ts.setFractionalOfSecond(getFractionalOfSecond() + rhs.getFractionalOfSecond());

    return ts;
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

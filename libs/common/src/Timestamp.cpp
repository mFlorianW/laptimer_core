#include "Timestamp.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>

namespace LaptimerCore::Common
{
class SharedTimestamp : public SharedData
{
public:
    std::uint8_t hour{0};
    std::uint8_t minute{0};
    std::uint8_t second{0};
    std::uint16_t fractionalOfSecond{0};

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

Timestamp::Timestamp(const std::string &timestampString)
    : mData{new SharedTimestamp{}}
{
    std::istringstream input(timestampString);
    std::string hour;
    std::getline(input, hour, ':');
    std::string minute;
    std::getline(input, minute, ':');
    std::string second;
    std::getline(input, second, '.');
    std::string fractionalOfSecond;
    std::getline(input, fractionalOfSecond);

    mData->hour = static_cast<std::uint8_t>(std::stoi(hour));
    mData->minute = static_cast<std::uint8_t>(std::stoi(minute));
    mData->second = static_cast<std::uint8_t>(std::stoi(second));
    mData->fractionalOfSecond = static_cast<std::uint16_t>(std::stoi(fractionalOfSecond));
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
    std::int32_t time1Msecs = convertToMilliSeconds();
    std::int32_t time2Msecs = rhs.convertToMilliSeconds();
    std::int32_t resultMsecs = time1Msecs + time2Msecs;

    std::int32_t resultHour = static_cast<std::int32_t>(resultMsecs / 3.6e6) % 24;
    std::int32_t resultMinute = static_cast<std::int32_t>(resultMsecs / 6e4) % 60;
    std::int32_t resultSeconds = static_cast<std::int32_t>(resultMsecs / 1e3) % 60;
    std::int32_t resultFractional = static_cast<std::int32_t>(resultMsecs) % 1000;

    Timestamp ts;
    ts.setHour(resultHour);
    ts.setMinute(resultMinute);
    ts.setSecond(resultSeconds);
    ts.setFractionalOfSecond(resultFractional);

    return ts;
}

Timestamp Timestamp::operator-(const Timestamp &rhs) const noexcept
{
    std::int32_t time1Msecs = convertToMilliSeconds();
    std::int32_t time2Msecs = rhs.convertToMilliSeconds();
    std::int32_t resultMsecs = time1Msecs - time2Msecs;

    std::int32_t resultHour = static_cast<std::int32_t>(resultMsecs / 3.6e6) % 24;
    std::int32_t resultMinute = static_cast<std::int32_t>(resultMsecs / 6e4) % 60;
    std::int32_t resultSeconds = static_cast<std::int32_t>(resultMsecs / 1e3) % 60;
    std::int32_t resultFractional = static_cast<std::int32_t>(resultMsecs) % 1000;

    Timestamp result;
    result.setHour(resultHour < 0 ? 24 + resultHour : resultHour);
    result.setMinute(resultMinute);
    result.setSecond(resultSeconds);
    result.setFractionalOfSecond(resultFractional);
    return result;
}

Timestamp Timestamp::getSystemTimestamp()
{
    const auto timeNow = std::chrono::system_clock::now();
    const auto timeT = std::chrono::system_clock::to_time_t(timeNow);
    const auto time = std::localtime(&timeT);
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(timeNow);
    auto fraction = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - seconds);

    auto timestamp = Timestamp{};
    timestamp.setHour(time->tm_hour);
    timestamp.setMinute(time->tm_min);
    timestamp.setSecond(time->tm_sec);
    timestamp.setFractionalOfSecond(fraction.count());

    return timestamp;
}

int32_t Timestamp::convertToMilliSeconds() const
{
    return (getHour() * 3.6e6) + (getMinute() * 6.0e4) + (getSecond() * 1e3) + getFractionalOfSecond();
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

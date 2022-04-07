#include "Date.hpp"
#include <iomanip>
#include <iostream>

namespace LaptimerCore::Common
{

class SharedDate : public SharedData
{
public:
    std::uint16_t mYear{0};
    std::uint8_t mMonth{0};
    std::uint8_t mDay{0};

    friend bool operator==(const SharedDate &lhs, const SharedDate &rhs)
    {
        // clang-format off
        return ((lhs.mYear == rhs.mYear) &&
                (lhs.mMonth == rhs.mMonth) &&
                (lhs.mDay == rhs.mDay));
        // clang-format on
    }
};

Date::Date()
    : mData{new SharedDate}
{
}

Date::Date(const std::string &dateString)
    : mData{new SharedDate}
{
    std::istringstream input(dateString);
    std::array<std::string, 3> splittedStrings;
    for (std::size_t i = 0; i < splittedStrings.size(); ++i)
    {
        getline(input, splittedStrings[i], '.');
    }

    mData->mDay = static_cast<std::uint8_t>(std::stoi(splittedStrings[0]));
    mData->mMonth = static_cast<std::uint8_t>(std::stoi(splittedStrings[1]));
    mData->mYear = static_cast<std::uint16_t>(std::stoi(splittedStrings[2]));
}

Date::~Date() = default;

Date::Date(const Date &other)
    : mData{other.mData}
{
}

Date &Date::operator=(const Date &other)
{
    mData = other.mData;
    return *this;
}

Date::Date(Date &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

Date &Date::operator=(Date &&other)
{
    Date moved{std::move(other)};
    std::swap(mData, moved.mData);
    return *this;
}

uint16_t Date::getYear() const noexcept
{
    return mData->mYear;
}

void Date::setYear(uint16_t year)
{
    mData->mYear = year;
}

uint8_t Date::getMonth() const noexcept
{
    return mData->mMonth;
}

void Date::setMonth(uint8_t month)
{
    mData->mMonth = month;
}

uint8_t Date::getDay() const noexcept
{
    return mData->mDay;
}

void Date::setDay(uint8_t day)
{
    mData->mDay = day;
}

std::string Date::asString() const noexcept
{
    std::ostringstream dateAsString;

    // clang-format off
    dateAsString << std::setw(2) << std::setfill('0') << std::to_string(getDay()) << "."
                 << std::setw(2) << std::setfill('0') << std::to_string(getMonth()) << "."
                 << std::setw(4) << std::setfill('0') << std::to_string(getYear());
    // clang-format on

    return dateAsString.str();
}

bool operator==(const Date &lhs, const Date &rhs)
{
    return lhs.mData == rhs.mData || *(lhs.mData) == *(rhs.mData);
}

bool operator!=(const Date &lhs, const Date &rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common

#include "Date.hpp"
#include <iomanip>
#include <iostream>

namespace LaptimerCore::Common
{

class SharedDateData : public SharedData
{
public:
    std::uint16_t mYear{0};
    std::uint8_t mMonth{0};
    std::uint8_t mDay{0};
};

Date::Date()
    : mData{new SharedDateData{}}
{
}

Date::~Date() = default;

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

} // namespace LaptimerCore::Common

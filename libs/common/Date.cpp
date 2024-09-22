// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "Date.hpp"
#include <array>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace LaptimerCore::Common
{

class SharedDate : public SharedData
{
public:
    std::uint16_t mYear{0};
    std::uint8_t mMonth{0};
    std::uint8_t mDay{0};

    friend bool operator==(SharedDate const& lhs, SharedDate const& rhs)
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

Date::Date(std::string const& dateString)
    : mData{new SharedDate}
{
    std::istringstream input(dateString);
    std::array<std::string, 3> splittedStrings;
    for (auto& splittedString : splittedStrings) {
        getline(input, splittedString, '.');
    }

    mData->mDay = static_cast<std::uint8_t>(std::stoi(splittedStrings[0]));
    mData->mMonth = static_cast<std::uint8_t>(std::stoi(splittedStrings[1]));
    mData->mYear = static_cast<std::uint16_t>(std::stoi(splittedStrings[2]));
}

Date::~Date() = default;
Date::Date(Date const& other) = default;
Date& Date::operator=(Date const& other) = default;
Date::Date(Date&& other) = default;
Date& Date::operator=(Date&& other) = default;

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

Date Date::getSystemDate() noexcept
{
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    auto const time = std::localtime(&timeT);

    auto date = Date{};
    date.setYear(1900 + time->tm_year); // The year is relativ to 1900.
    date.setMonth(++time->tm_mon); // The month is in the range 0-11.
    date.setDay(time->tm_mday);
    return date;
}

bool operator==(Date const& lhs, Date const& rhs)
{
    return lhs.mData == rhs.mData || *(lhs.mData) == *(rhs.mData);
}

bool operator!=(Date const& lhs, Date const& rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Common

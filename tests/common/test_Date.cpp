// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "Date.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;

TEST_CASE("The Date shall be convertable to a string in format DD.MM.YYYY")
{
    constexpr char expectedResult[] = "01.01.1970";
    Date date;
    date.setDay(1);
    date.setMonth(1);
    date.setYear(1970);

    auto result = date.asString();

    REQUIRE(result == expectedResult);
}

TEST_CASE("The Date shall be creatable from string in the format of dd.MM.YYYY")
{
    Date expectedDate;
    expectedDate.setDay(1);
    expectedDate.setMonth(1);
    expectedDate.setYear(1970);

    auto date = Date{"01.01.1970"};
    REQUIRE(date == expectedDate);
}

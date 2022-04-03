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

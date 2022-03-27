#define CATCH_CONFIG_MAIN
#include "Timestamp.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;

TEST_CASE("A Timestamp shall be able to convert the time into a string.")
{
    constexpr char expectedResult[] = "00:01:35.123";
    Timestamp timestamp;
    timestamp.setHour(0);
    timestamp.setMinute(1);
    timestamp.setSecond(35);
    timestamp.setFractionalOfSecond(123);

    const auto result = timestamp.asString();

    REQUIRE(result == expectedResult);
}

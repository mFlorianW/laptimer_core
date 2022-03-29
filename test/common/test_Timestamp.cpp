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

TEST_CASE("It shall be possible to compare two timestamps for equal.")
{
    Timestamp ts1;
    ts1.setHour(1);
    ts1.setMinute(2);
    ts1.setSecond(25);
    ts1.setFractionalOfSecond(134);
    Timestamp ts2;
    ts2.setHour(1);
    ts2.setMinute(2);
    ts2.setSecond(25);
    ts2.setFractionalOfSecond(134);

    REQUIRE(ts1 == ts2);
}

TEST_CASE("It shall be possible to calucalte the sum of two timestamps.")
{
    Timestamp ts1;
    ts1.setHour(1);
    ts1.setMinute(2);
    ts1.setSecond(25);
    ts1.setFractionalOfSecond(134);
    Timestamp ts2;
    ts2.setHour(3);
    ts2.setMinute(0);
    ts2.setSecond(25);
    ts2.setFractionalOfSecond(144);

    Timestamp expectedResult;
    expectedResult.setHour(4);
    expectedResult.setMinute(2);
    expectedResult.setSecond(50);
    expectedResult.setFractionalOfSecond(278);

    auto result = ts1 + ts2;

    REQUIRE(result == expectedResult);
}

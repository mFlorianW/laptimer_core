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

TEST_CASE("The plus operator of timestamp shall handle hour overflow when passing midnight.")
{
    Timestamp ts1;
    ts1.setHour(22);
    ts1.setMinute(0);
    ts1.setSecond(0);
    ts1.setFractionalOfSecond(0);
    Timestamp ts2;
    ts2.setHour(3);
    ts2.setMinute(0);
    ts2.setSecond(0);
    ts2.setFractionalOfSecond(0);

    Timestamp expectedResult;
    expectedResult.setHour(1);
    expectedResult.setMinute(0);
    expectedResult.setSecond(0);
    expectedResult.setFractionalOfSecond(0);

    auto result = ts1 + ts2;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The plus operator of timestamp shall handle minute overflow when passing 60 minutes.")
{
    Timestamp ts1;
    ts1.setHour(0);
    ts1.setMinute(58);
    ts1.setSecond(0);
    ts1.setFractionalOfSecond(0);
    Timestamp ts2;
    ts2.setHour(0);
    ts2.setMinute(12);
    ts2.setSecond(0);
    ts2.setFractionalOfSecond(0);

    Timestamp expectedResult;
    expectedResult.setHour(1);
    expectedResult.setMinute(10);
    expectedResult.setSecond(0);
    expectedResult.setFractionalOfSecond(0);

    auto result = ts1 + ts2;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The plus operator of timestamp shall handle second overflow when passing 60 seconds.")
{
    Timestamp ts1;
    ts1.setHour(0);
    ts1.setMinute(0);
    ts1.setSecond(42);
    ts1.setFractionalOfSecond(0);
    Timestamp ts2;
    ts2.setHour(0);
    ts2.setMinute(0);
    ts2.setSecond(32);
    ts2.setFractionalOfSecond(0);

    Timestamp expectedResult;
    expectedResult.setHour(0);
    expectedResult.setMinute(1);
    expectedResult.setSecond(14);
    expectedResult.setFractionalOfSecond(0);

    auto result = ts1 + ts2;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The plus operator of timestamp shall handle millisecond overflow when passing 1000 ms.")
{
    Timestamp ts1;
    ts1.setHour(0);
    ts1.setMinute(0);
    ts1.setSecond(0);
    ts1.setFractionalOfSecond(300);
    Timestamp ts2;
    ts2.setHour(0);
    ts2.setMinute(0);
    ts2.setSecond(0);
    ts2.setFractionalOfSecond(800);

    Timestamp expectedResult;
    expectedResult.setHour(0);
    expectedResult.setMinute(0);
    expectedResult.setSecond(1);
    expectedResult.setFractionalOfSecond(100);

    auto result = ts1 + ts2;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The Timestamp shall support minus operations with a other Timestamp.")
{
    Timestamp ts1;
    ts1.setHour(1);
    ts1.setMinute(2);
    ts1.setSecond(0);
    ts1.setFractionalOfSecond(134);
    Timestamp ts2;
    ts2.setHour(3);
    ts2.setMinute(5);
    ts2.setSecond(25);
    ts2.setFractionalOfSecond(144);

    Timestamp expectedResult;
    expectedResult.setHour(2);
    expectedResult.setMinute(3);
    expectedResult.setSecond(25);
    expectedResult.setFractionalOfSecond(10);

    auto result = ts2 - ts1;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The Timestamp shall handle hour underflow in the minus operation.")
{
    Timestamp ts1;
    ts1.setHour(5);
    ts1.setMinute(0);
    ts1.setSecond(0);
    ts1.setFractionalOfSecond(0);
    Timestamp ts2;
    ts2.setHour(3);
    ts2.setMinute(0);
    ts2.setSecond(0);
    ts2.setFractionalOfSecond(0);

    Timestamp expectedResult;
    expectedResult.setHour(22);
    expectedResult.setMinute(0);
    expectedResult.setSecond(0);
    expectedResult.setFractionalOfSecond(0);

    auto result = ts2 - ts1;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The Timestamp shall handle minute underflow in the minus operation.")
{
    Timestamp ts1;
    ts1.setHour(1);
    ts1.setMinute(48);
    ts1.setSecond(0);
    ts1.setFractionalOfSecond(0);
    Timestamp ts2;
    ts2.setHour(5);
    ts2.setMinute(2);
    ts2.setSecond(0);
    ts2.setFractionalOfSecond(0);

    Timestamp expectedResult;
    expectedResult.setHour(4);
    expectedResult.setMinute(14);
    expectedResult.setSecond(0);
    expectedResult.setFractionalOfSecond(0);

    auto result = ts2 - ts1;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The Timestamp shall handle second underflow in the minus operation.")
{
    Timestamp ts1;
    ts1.setHour(1);
    ts1.setMinute(48);
    ts1.setSecond(55);
    ts1.setFractionalOfSecond(0);
    Timestamp ts2;
    ts2.setHour(5);
    ts2.setMinute(2);
    ts2.setSecond(5);
    ts2.setFractionalOfSecond(0);

    Timestamp expectedResult;
    expectedResult.setHour(4);
    expectedResult.setMinute(14);
    expectedResult.setSecond(10);
    expectedResult.setFractionalOfSecond(0);

    auto result = ts2 - ts1;

    REQUIRE(result == expectedResult);
}

TEST_CASE("The Timestamp shall handle fractional of second underflow in the minus operation.")
{
    Timestamp ts1;
    ts1.setHour(1);
    ts1.setMinute(48);
    ts1.setSecond(55);
    ts1.setFractionalOfSecond(500);
    Timestamp ts2;
    ts2.setHour(5);
    ts2.setMinute(2);
    ts2.setSecond(5);
    ts2.setFractionalOfSecond(128);

    Timestamp expectedResult;
    expectedResult.setHour(4);
    expectedResult.setMinute(14);
    expectedResult.setSecond(10);
    expectedResult.setFractionalOfSecond(628);

    auto result = ts2 - ts1;

    REQUIRE(result == expectedResult);
}

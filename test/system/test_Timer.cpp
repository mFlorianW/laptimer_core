#define CATCH_CONFIG_MAIN
#include "Timer.hpp"
#include <catch2/catch.hpp>
#include <thread>

using namespace LaptimerCore::System;

TEST_CASE("The timer shall emit the timeout event after the elapsed time set by the interval.")
{
    auto timeoutEventEmitted = false;
    auto timer = Timer{};
    timer.setInterval(std::chrono::milliseconds(3));
    timer.timeout.connect([&]() { timeoutEventEmitted = true; });

    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    handleTimerTicks();

    REQUIRE(timeoutEventEmitted == true);
}

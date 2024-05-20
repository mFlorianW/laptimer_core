// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "CompareHelper.hpp"
#include "EventLoop.hpp"
#include "Timer.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::System;
using namespace LaptimerCore::Testhelper;
using namespace std::chrono;

TEST_CASE("The timer shall emit the timeout event after the elapsed time set by the interval.")
{
    auto eventloop = EventLoop{};

    auto timeoutEventEmitted = false;
    auto timer = Timer{};
    timer.setInterval(std::chrono::milliseconds(3));
    auto timeoutTime = long{0};
    auto timerStartMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    timer.timeout.connect([&]() {
        timeoutEventEmitted = true;
        auto timeoutMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        timeoutTime = timeoutMs - timerStartMs;
        timer.stop();
    });
    timer.start();
    REQUIRE(timer.isRunning());
    REQUIRE_COMPARE_WITH_TIMEOUT(timeoutEventEmitted, true, std::chrono::milliseconds{1000});
    CHECK_THAT(timeoutTime, IsBetweenMatcher(2, 4));

    auto timeout1EventEmitted = true;
    auto timer1 = Timer{};
    auto timeout1Time = long{0};
    timer1.setInterval(std::chrono::milliseconds(5));
    timerStartMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    timer1.timeout.connect([&]() {
        timeout1EventEmitted = true;
        auto timeoutMs = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        timeout1Time = timeoutMs - timerStartMs;
        timer1.stop();
    });
    timer1.start();
    REQUIRE_COMPARE_WITH_TIMEOUT(timeout1EventEmitted, true, std::chrono::milliseconds{1000});
    CHECK_THAT(timeout1Time, IsBetweenMatcher(4, 6));
}

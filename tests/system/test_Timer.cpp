// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "SignalDispatcher.hpp"
#include "Timer.hpp"
#include <catch2/catch.hpp>
#include <thread>

using namespace LaptimerCore::System;

TEST_CASE("The timer shall emit the timeout event after the elapsed time set by the interval.")
{
    auto dispatcher = SignalDispatcher{};
    auto timeoutEventEmitted = false;
    auto timer = Timer{};
    timer.setInterval(std::chrono::milliseconds(3));
    timer.timeout.connect([&]() {
        timeoutEventEmitted = true;
    });

    timer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    dispatcher.exec();

    REQUIRE(timeoutEventEmitted == true);
}

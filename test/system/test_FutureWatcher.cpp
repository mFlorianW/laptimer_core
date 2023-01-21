#define CATCH_CONFIG_MAIN
#include "FutureWatcher.hpp"
#include <catch2/catch.hpp>
#include <thread>

using namespace LaptimerCore::System;

void sleepy(std::promise<void> promise)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    promise.set_value();
}

void returny(std::promise<bool> promise)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    promise.set_value(true);
}

SCENARIO("The FutureWatcher shall emit the finish signal when the future finishes.", "[FutureWatcher]")
{
    GIVEN("A initialized FutureWatcher")
    {
        auto finishSignalEmitted = false;
        auto sleepyPromise = std::promise<void>{};
        auto futureWatcher = FutureWatcher<void>{sleepyPromise.get_future()};
        futureWatcher.finished.connect([&finishSignalEmitted]() { finishSignalEmitted = true; });

        WHEN("Observed operation is finished")
        {
            auto thread = std::thread(&sleepy, std::move(sleepyPromise));
            thread.join();

            THEN("The finished signal should be emitted")
            {
                SignalDispatcher{}.exec();
                REQUIRE(finishSignalEmitted == true);
            }
        }
    }
}

SCENARIO("The FutureWatcher shall be to return the result of the observed future.", "[FutureWatcher]")
{
    GIVEN("A initialized FutureWatcher")
    {
        auto returnyPromise = std::promise<bool>{};
        auto futureWatcher = FutureWatcher<bool>{returnyPromise.get_future()};

        WHEN("Observed operation is finished")
        {
            auto thread = std::thread(&returny, std::move(returnyPromise));
            thread.join();

            THEN("The correct value of the future shall be returned")
            {
                SignalDispatcher{}.exec();
                REQUIRE(futureWatcher.getResult() == true);
            }
        }
    }
}

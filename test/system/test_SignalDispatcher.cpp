#define CATCH_CONFIG_MAIN
#include "SignalDispatcher.hpp"
#include "kdbindings/signal.h"
#include <catch2/catch.hpp>
#include <future>
#include <thread>

using namespace LaptimerCore::System;

class TestDispatcherObject : public IDispatcherObject
{
public:
    void dispatch() override
    {
        signal.emit();
    }

    KDBindings::Signal<> signal;
};

SCENARIO("The SignalDispatcher shall dispatch signal of registered DispatcherObject")
{
    GIVEN("A SignalDispatcher")
    {
        auto testDispatcherObject = TestDispatcherObject{};
        auto signalDispatcher = SignalDispatcher{};
        signalDispatcher.registerObject(&testDispatcherObject, std::this_thread::get_id());
        auto signalEmitted = false;
        testDispatcherObject.signal.connect([&]() { signalEmitted = true; });

        WHEN("SignalDispatcher is exec is called the signal shall be dispatched")
        {
            signalDispatcher.exec();

            THEN("The signal spy should be set")
            {
                REQUIRE(signalEmitted == true);
            }
        }
    }
}

SCENARIO("The SignalDispatcher shall ignore exec calls from threads other than the owner thread")
{
    GIVEN("A SignalDispatcher")
    {
        auto testDispatcherObject = TestDispatcherObject{};
        auto signalDispatcher = SignalDispatcher{};
        signalDispatcher.registerObject(&testDispatcherObject, std::this_thread::get_id());
        auto signalEmitted = false;
        testDispatcherObject.signal.connect([&]() { signalEmitted = true; });

        WHEN("SignalDispatcher exec called from other thread")
        {
            auto thread = std::thread(&SignalDispatcher::exec, &signalDispatcher);
            thread.join();

            THEN("The signal spy shouldn't be set")
            {
                REQUIRE(signalEmitted == false);
            }
        }
    }
}

SCENARIO("The SignalDispatcher shall only register objects from the same thread")
{

    GIVEN("A SignalDispatcher")
    {
        auto signalDispatcher = SignalDispatcher{};

        WHEN("Register object from the same thread")
        {
            auto testDispatcherObject = TestDispatcherObject{};
            const auto registerResult =
                signalDispatcher.registerObject(&testDispatcherObject, std::this_thread::get_id());

            THEN("The registration should be successful")
            {
                REQUIRE(registerResult == Result::Ok);
            }
        }

        WHEN("The registration of the object is called from other thread than the owning thread")
        {
            auto testDispatcherObject = TestDispatcherObject{};
            auto registerResult = std::promise<Result>{};
            auto thread = std::thread([&]() {
                registerResult.set_value(
                    signalDispatcher.registerObject(&testDispatcherObject, std::this_thread::get_id()));
            });
            auto future = registerResult.get_future();
            future.wait();
            thread.join();

            THEN("The registration of the object should fail")
            {
                REQUIRE(future.get() == Result::Error);
            }
        }
    }
}

SCENARIO("The SignalDispatcher shall only unregister objects from the same thread")
{
    GIVEN("A SignalDispatcher")
    {
        auto signalDispatcher = SignalDispatcher{};

        WHEN("Register object from the same thread")
        {
            auto testDispatcherObject = TestDispatcherObject{};
            signalDispatcher.registerObject(&testDispatcherObject, std::this_thread::get_id());
            const auto unregisterResult =
                signalDispatcher.unregisterObject(&testDispatcherObject, std::this_thread::get_id());

            THEN("The uregistration should be successful")
            {
                REQUIRE(unregisterResult == Result::Ok);
            }
        }

        WHEN("The unregistration for the object is called from other thread than the owning thread")
        {
            auto testDispatcherObject = TestDispatcherObject{};
            auto unregisterResult = std::promise<Result>{};
            signalDispatcher.registerObject(&testDispatcherObject, std::this_thread::get_id());
            auto thread = std::thread([&]() {
                unregisterResult.set_value(
                    signalDispatcher.unregisterObject(&testDispatcherObject, std::this_thread::get_id()));
            });
            auto future = unregisterResult.get_future();
            future.wait();
            thread.join();

            THEN("The registration of the object should fail")
            {
                REQUIRE(future.get() == Result::Error);
            }
        }
    }
}

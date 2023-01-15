#define CATCH_CONFIG_MAIN
#include "SignalDispatcher.hpp"
#include "kdbindings/signal.h"
#include <catch2/catch.hpp>

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
        signalDispatcher.registerObject(&testDispatcherObject);
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

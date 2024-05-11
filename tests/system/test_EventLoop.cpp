// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "Event.hpp"
#include "EventLoop.hpp"
#include <catch2/catch.hpp>
#include <thread>

using namespace LaptimerCore::System;

class TestEventReceiver : public EventReceiver
{

public:
    bool eventReceived = false;
    std::thread::id tid = std::thread::id{0};
    std::size_t handleEventCallCount = 0;

    bool handleEvent(Event* e) override
    {
        tid = std::this_thread::get_id();
        eventReceived = true;
        ++handleEventCallCount;
        return true;
    }
};

SCENARIO("An EventLoop shall call the receiver of an Event.")
{
    GIVEN("An Eventloop and EventReceiver")
    {
        auto eventLoop = EventLoop{};
        auto eventReceiver = TestEventReceiver{};
        WHEN("An event is posted to the loop and process events")
        {
            eventLoop.postEvent(&eventReceiver, std::make_unique<Event>());
            eventLoop.processEvents();
            THEN("The event shall be delivered to the receiver")
            {
                REQUIRE(eventReceiver.eventReceived);
            }
        }
    }
}

SCENARIO("Process posted events from a different thread in the receivers EventLoop")
{
    GIVEN("An EventLoop and EventReceiver")
    {
        auto eventLoop = EventLoop{};
        auto eventReceiver = TestEventReceiver{};
        auto const threadId = std::this_thread::get_id();
        WHEN("Posting event from a different thread")
        {
            auto thread = std::thread{[&eventLoop, &eventReceiver]() {
                eventLoop.postEvent(&eventReceiver, std::make_unique<Event>());
            }};
            thread.join();
            eventLoop.processEvents();
            THEN("Event function is called in the receivers thread")
            {
                REQUIRE(eventReceiver.tid == threadId);
            }
        }
    }
}

SCENARIO("Process events when called from the owning thread.")
{
    GIVEN("An Eventloop and EventReceiver")
    {
        auto eventLoop = EventLoop{};
        auto eventReceiver = TestEventReceiver{};
        WHEN("Process events from a different thread")
        {
            auto thread = std::thread{[&eventLoop, &eventReceiver]() {
                eventLoop.postEvent(&eventReceiver, std::make_unique<Event>());
                eventLoop.processEvents();
            }};
            thread.join();
            THEN("The eventloop doesn't process events")
            {
                REQUIRE(eventReceiver.eventReceived == false);
            }
        }
    }
}

SCENARIO("Every thread shall have it's own event loop and events for a specific thread shall be processed")
{
    GIVEN("Threads with EventLoops")
    {
        auto tid1 = std::thread::id{0};
        auto tid11 = std::thread::id{0};
        auto thread1 = std::thread{[&tid1]() {
            auto eventLoop = EventLoop{};
            auto eventReceiver = TestEventReceiver{};
            eventLoop.postEvent(&eventReceiver, std::make_unique<Event>());
            std::this_thread::sleep_for(std::chrono::milliseconds{3});
            eventLoop.processEvents();
            tid1 = eventReceiver.tid;
        }};
        tid11 = thread1.get_id();

        auto tid2 = std::thread::id{0};
        auto tid22 = std::thread::id{0};
        auto thread2 = std::thread{[&tid2]() {
            auto eventLoop = EventLoop{};
            auto eventReceiver = TestEventReceiver{};
            eventLoop.postEvent(&eventReceiver, std::make_unique<Event>());
            std::this_thread::sleep_for(std::chrono::milliseconds{1});
            eventLoop.processEvents();
            tid2 = eventReceiver.tid;
        }};
        tid22 = thread2.get_id();

        WHEN("The threads are done")
        {
            thread1.join();
            thread2.join();
            THEN("Only the events should only be called once. In each thread.")
            {
                REQUIRE(tid11 == tid1);
                REQUIRE(tid22 == tid2);
            }
        }
    }
}

SCENARIO("An Eventloop shall block the running thread until the quit event occurs")
{
    GIVEN("An EventLoop")
    {
        auto eventloop = EventLoop{};
        WHEN("The quit event is posted to the EventLoop")
        {
            auto thread = std::thread([&eventloop] {
                std::this_thread::sleep_for(std::chrono::milliseconds{1});
                eventloop.postEvent(&eventloop, std::make_unique<Event>(Event::Type::QuitEvent));
            });
            eventloop.exec();
            THEN("The EventLoop exit")
            {
                thread.join();
                REQUIRE(true);
            }
        }
    }
}

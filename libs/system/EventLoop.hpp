// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "Event.hpp"
#include "EventHandler.hpp"
#include <memory>
#include <thread>

namespace LaptimerCore::System
{

/**
 * Provides functions to post, process events and can start an event loop.
 */
class EventLoop final
{
public:
    /**
     * Default consturctor
     */
    EventLoop();

    /**
     * Default destructor
     */
    ~EventLoop();

    /**
     * Disabled copy consturctor
     */
    EventLoop(EventLoop const&) = delete;

    /**
     * Disabled move constructor
     */
    EventLoop(EventLoop&&) noexcept = delete;

    /**
     * Disabled move operator
     */
    EventLoop& operator=(EventLoop const&) = delete;

    /**
     * Disabled copy assignment operator
     */
    EventLoop& operator=(EventLoop&&) noexcept = default;

    /**
     * Post an event for the receiver
     * @param receiver The receiver that shall receive the event.
     */
    static void postEvent(EventHandler* receiver, std::unique_ptr<Event> event);

    /**
     * Checks if for an existing event of @ref Event::Type type in the event loop
     * @return true Event is present, otherwise false.
     */
    bool isEventQueued(EventHandler* receiver, Event::Type type) const noexcept;

    /**
     * Process all queue events and then returns
     */
    void processEvents();

    /**
     * Starts a mainloop, blocks and runs infinite until exit was called.
     */
    void exec();

    /**
     * Stops and quits an endless running eventloop
     */
    void quit() noexcept;

private:
    friend class LaptimerCore::System::EventHandler;
    /**
     * Clear all events for a specific event handler
     */
    static void clearEvents(EventHandler* eventHandler) noexcept;

    std::thread::id mOwningThread;
};

} // namespace LaptimerCore::System

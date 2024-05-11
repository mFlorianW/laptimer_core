// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "Event.hpp"
#include "EventReceiver.hpp"
#include <memory>
#include <thread>

namespace LaptimerCore::System
{

/**
 * Provides functions to post, process events and can start an event loop.
 */
class EventLoop : public EventReceiver
{
public:
    /**
     * Default consturctor
     */
    EventLoop();

    /**
     * Default destructor
     */
    ~EventLoop() override;

    /**
     * Disabled copy consturctor
     */
    EventLoop(EventLoop const&) = delete;

    /**
     * Disabled move constructor
     */
    EventLoop(EventLoop&&) noexcept = delete;

    EventLoop& operator=(EventLoop const&) = delete;

    /**
     * Disabled copy assignment operator
     */
    EventLoop& operator=(EventLoop&&) noexcept = default;

    /**
     * Post an event for the receiver
     * @param receiver The receiver that shall receive the event.
     */
    void postEvent(EventReceiver* receiver, std::unique_ptr<Event> event);

    /**
     * Process all queue events and then returns
     */
    void processEvents();

    /**
     * Starts a mainloop, blocks and runs infinite until exit was called.
     */
    void exec();

    /**
     * Handle events for the Eventloop.
     * This is basically only the quit event.
     */
    bool handleEvent(Event* event) override;

private:
    std::thread::id mOwingThread = std::thread::id{0};
};

} // namespace LaptimerCore::System
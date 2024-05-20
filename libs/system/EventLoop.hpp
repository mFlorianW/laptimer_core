// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "Event.hpp"
#include "EventReceiver.hpp"
#include <atomic>
#include <memory>
#include <thread>
#include <unordered_map>

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
     * Checks if for an existing event of @ref Event::Type type in the event loop
     * @return true Event is present, otherwise false.
     */
    bool isEventQueued(EventReceiver* receiver, Event::Type type) const noexcept;

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
    static std::unordered_map<std::thread::id, std::atomic_uint32_t>
        mInstances; // NOLINT cppcoreguidelines-avoid-non-const-global-variables
    std::thread::id mOwningThread;
};

} // namespace LaptimerCore::System

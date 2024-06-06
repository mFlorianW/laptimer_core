// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "EventLoop.hpp"
#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <unordered_map>

namespace LaptimerCore::System
{

class EventQueue
{
public:
    EventQueue() = default;

    static EventQueue& getInstance(std::thread::id const& tid)
    {
        static std::mutex mutex;
        static std::unordered_map<std::thread::id, std::unique_ptr<EventQueue>> eventQueues;
        if (eventQueues.count(tid) == 0) {
            std::lock_guard<std::mutex> guard{mutex};
            eventQueues.emplace(tid, std::make_unique<EventQueue>());
        }
        return *eventQueues[tid];
    }

    void postEvent(EventHandler* receiver, std::unique_ptr<Event> event, std::thread::id const& tid)
    {

        if (tid != receiver->getThreadId()) {
            std::cerr
                << "The event receiver has a different thread affinity. Event posted to wrong event loop instance.";
            return;
        }

        std::lock_guard<std::mutex> guard{mMutex};
        mEventQueue.push_back(EventQueueEntry{.receiver = receiver, .event = std::move(event)});
        mBlocker.notify_all();
    }

    void processEvents()
    {
        auto iter = mEventQueue.begin();
        while (iter != mEventQueue.end()) {
            auto event = std::move(iter->event);
            auto* receiver = iter->receiver;
            iter = mEventQueue.erase(iter);
            receiver->handleEvent(event.get());
        }
    }

    void exec()
    {
        mRunning = true;
        while (mRunning) {
            if (not mRunning) {
                break;
            }
            std::unique_lock uLock{mMutex};
            mBlocker.wait(uLock);
            processEvents();
        }
    }

    void clearQueue()
    {
        mEventQueue.clear();
    }

    void stopEventLoop()
    {
        {
            std::lock_guard<std::mutex> guard{mMutex};
            mRunning = false;
        }
        mBlocker.notify_one();
    }

    bool isEventQueued(EventHandler* receiver, Event::Type type) const noexcept
    {
        for (auto const& entry : mEventQueue) {
            if (entry.receiver == receiver and entry.event->getEventType() == type) {
                return true;
            }
        }
        return false;
    }

    void clearEvents(EventHandler* eventHandler)
    {
        auto iter = mEventQueue.begin();
        while (iter != mEventQueue.end()) {
            if (iter->receiver == eventHandler) {
                std::lock_guard<std::mutex> guard{mMutex};
                iter = mEventQueue.erase(iter);
            } else {
                ++iter;
            }
        }
    }

private:
    struct EventQueueEntry
    {
        EventHandler* receiver;
        std::unique_ptr<Event> event;
    };
    std::deque<EventQueueEntry> mEventQueue;
    mutable std::mutex mMutex;
    std::condition_variable mBlocker;
    bool mRunning = false;
};

EventLoop::EventLoop()
    : mOwningThread{std::this_thread::get_id()}
{
}

EventLoop::~EventLoop() = default;

void EventLoop::postEvent(EventHandler* receiver, std::unique_ptr<Event> event)
{
    EventQueue::getInstance(receiver->getThreadId()).postEvent(receiver, std::move(event), receiver->getThreadId());
}

bool EventLoop::isEventQueued(EventHandler* receiver, Event::Type type) const noexcept
{
    return EventQueue::getInstance(mOwningThread).isEventQueued(receiver, type);
}

void EventLoop::processEvents()
{
    if (std::this_thread::get_id() != mOwningThread) {
        std::cerr << "Events can only be processed from the EventLoop owning thread.\n";
        std::cerr << "Owning thread: " << mOwningThread << " Calling thread: " << std::this_thread::get_id() << "\n";
        return;
    }
    EventQueue::getInstance(mOwningThread).processEvents();
}

void EventLoop::exec()
{
    if (std::this_thread::get_id() != mOwningThread) {
        std::cerr << "Exec can only be called from the Eventloop owning thread.\n";
        std::cerr << "Owning thread: " << mOwningThread << " Calling thread: " << std::this_thread::get_id() << "\n";
    }
    EventQueue::getInstance(mOwningThread).exec();
}

void EventLoop::quit() noexcept
{
    EventQueue::getInstance(mOwningThread).stopEventLoop();
}

void EventLoop::clearEvents(EventHandler* eventHandler) noexcept
{
    EventQueue::getInstance(eventHandler->getThreadId()).clearEvents(eventHandler);
}

} // namespace LaptimerCore::System

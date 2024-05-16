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
        static std::unordered_map<std::thread::id, std::unique_ptr<EventQueue>> eventQueues;
        if (eventQueues.count(tid) == 0) {
            eventQueues.emplace(tid, std::make_unique<EventQueue>());
        }
        return *eventQueues[tid];
    }

    void postEvent(EventReceiver* receiver, std::unique_ptr<Event> event, std::thread::id const& tid)
    {

        if (tid != receiver->getThreadId()) {
            std::cerr
                << "The event receiver has a different thread affinity. Event posted to wrong event loop instance.";
            return;
        }
        if (event->getEventType() == Event::Type::QuitEvent) {
            stopEventLoop();
        } else {
            std::lock_guard<std::mutex> guard{mMutex};
            mEventQueue.push_back(EventQueueEntry{.receiver = receiver, .event = std::move(event)});
            mBlocker.notify_all();
        }
    }

    void processEvents()
    {
        auto iter = mEventQueue.begin();
        while (iter != mEventQueue.end()) {
            iter->receiver->handleEvent(iter->event.get());
            iter = mEventQueue.erase(iter);
        }
    }

    void exec()
    {
        mRunning = true;
        while (mRunning) {
            std::unique_lock uLock{mMutex};
            mBlocker.wait(uLock);
            if (not mRunning) {
                break;
            }
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
        mEventQueue.clear();
        mBlocker.notify_one();
    }

    bool isEventQueued(EventReceiver* receiver, Event::Type type) const noexcept
    {
        for (auto const& entry : mEventQueue) {
            if (entry.receiver == receiver and entry.event->getEventType() == type) {
                return true;
            }
        }
        return false;
    }

private:
    struct EventQueueEntry
    {
        EventReceiver* receiver;
        std::unique_ptr<Event> event;
    };
    std::deque<EventQueueEntry> mEventQueue;
    mutable std::mutex mMutex;
    std::condition_variable mBlocker;
    bool mRunning = false;
};

std::unordered_map<std::thread::id, std::atomic_uint32_t>
    EventLoop::EventLoop::mInstances = // NOLINT cppcoreguidelines-avoid-non-const-global-variables
    std::unordered_map<std::thread::id, std::atomic_uint32_t>{};

EventLoop::EventLoop()
    : mOwningThread{std::this_thread::get_id()}
{
    if (mInstances.count(mOwningThread) == 0) {
        mInstances.emplace(mOwningThread, 1);
    } else {
        mInstances[mOwningThread]++;
    }
}

EventLoop::~EventLoop()
{
    mInstances[mOwningThread]--;
    if (mInstances[mOwningThread] == 0) {
        EventQueue::getInstance(mOwningThread).clearQueue();
    }
}

void EventLoop::postEvent(EventReceiver* receiver, std::unique_ptr<Event> event)
{
    EventQueue::getInstance(mOwningThread).postEvent(receiver, std::move(event), receiver->getThreadId());
}

bool EventLoop::isEventQueued(EventReceiver* receiver, Event::Type type) const noexcept
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

bool EventLoop::handleEvent(Event* event)
{
    if (event->getEventType() == Event::Type::QuitEvent) {
        EventQueue::getInstance(mOwningThread).stopEventLoop();
        return true;
    }
    return false;
}

} // namespace LaptimerCore::System

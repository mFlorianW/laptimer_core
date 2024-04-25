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
        std::lock_guard<std::mutex> guard{mMutex};
        if (tid != receiver->getThreadId()) {
            std::cerr
                << "The event receiver has a different thread affinity. Event posted to wrong event loop instance.";
            return;
        }
        mEventQueue.push_back(EventQueueEntry{.receiver = receiver, .event = std::move(event)});
        mBlocker.notify_one();
    }

    void processEvents()
    {
        std::lock_guard<std::mutex> guard{mMutex};
        auto iter = mEventQueue.begin();
        while (iter != mEventQueue.end()) {
            iter->receiver->handleEvent(iter->event.get());
            iter = mEventQueue.erase(iter);
        }
    }

    void exec()
    {
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
        mRunning = false;
        mEventQueue.clear();
        mBlocker.notify_one();
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

EventLoop::EventLoop()
    : mOwingThread{std::this_thread::get_id()}
{
}

EventLoop::~EventLoop()
{
    EventQueue::getInstance(mOwingThread).clearQueue();
}

void EventLoop::postEvent(EventReceiver* receiver, std::unique_ptr<Event> event)
{
    EventQueue::getInstance(mOwingThread).postEvent(receiver, std::move(event), receiver->getThreadId());
}

void EventLoop::processEvents()
{
    if (std::this_thread::get_id() != mOwingThread) {
        std::cerr << "Events can only be processed from the EventLoop owning thread.\n";
        std::cerr << "Owning thread: " << mOwingThread << " Calling thread: " << std::this_thread::get_id() << "\n";
        return;
    }

    EventQueue::getInstance(mOwingThread).processEvents();
}

void EventLoop::exec()
{
    if (std::this_thread::get_id() != mOwingThread) {
        std::cerr << "Exec can only be called from the Eventloop owning thread.\n";
        std::cerr << "Owning thread: " << mOwingThread << " Calling thread: " << std::this_thread::get_id() << "\n";
    }
    EventQueue::getInstance(mOwingThread).exec();
}

bool EventLoop::handleEvent(Event* event)
{
    if (event->getEventType() == Event::Type::QuitEvent) {
        EventQueue::getInstance(mOwingThread).stopEventLoop();
        return true;
    }
    return false;
}

} // namespace LaptimerCore::System

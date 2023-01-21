#pragma once

#include "IDispatcherObject.hpp"
#include "SignalDispatcher.hpp"
#include <future>
#include <iostream>
#include <kdbindings/signal.h>
#include <set>
#include <unordered_set>

namespace LaptimerCore::System
{

template <class T>
class FutureWatcher : public IDispatcherObject
{
public:
    /**
     * Creates FutureWatcher instance
     */
    FutureWatcher() noexcept = default;

    /**
     * Creates a FutureWatcher instance and starts observing the future.
     * @param future The future to observe
     */
    FutureWatcher(std::future<T> future) noexcept
    {
        setFuture(std::move(future));
    }

    /**
     * default constructor
     */
    ~FutureWatcher() noexcept override
    {
        if (mFutureObserver.joinable())
        {
            mFutureObserver.join();
        }

        SignalDispatcher{}.unregisterObject(this, std::this_thread::get_id());
    }

    /**
     * Deleted copy constructor
     */
    FutureWatcher(const FutureWatcher &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    FutureWatcher &operator=(const FutureWatcher &other) = delete;

    /**
     * Deleted move constructor
     */
    FutureWatcher(FutureWatcher &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    FutureWatcher &operator=(FutureWatcher &&other) = delete;

    /**
     * Sets a future and starts observing the future.
     * @param The future to observe.
     */
    void setFuture(std::future<T> future) noexcept
    {
        mFuture = std::move(future);
        SignalDispatcher{}.registerObject(this, std::this_thread::get_id());
        mFutureObserver = std::thread([this]() {
            mFuture.wait();
            mFinished = true;
        });
    }

    /**
     * Gives the result of the future. If the still running the function will block and waits until the future is ready.
     * @return The Result of the underlying future.
     */
    [[nodiscard]] T getResult() noexcept
    {
        return mFuture.get();
    }

    /**
     * This signal is emitted when the observed future execution is finished.
     */
    KDBindings::Signal<> finished;

protected:
    void dispatch() override
    {
        if (mFinished)
        {
            finished.emit();
        }
    }

private:
    void futureWatcher() const noexcept
    {
        mFuture.wait();
    }

private:
    std::atomic_bool mFinished{false};
    std::thread mFutureObserver{};
    std::future<T> mFuture{};
};

} // namespace LaptimerCore::System

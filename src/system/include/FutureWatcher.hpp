#pragma once

#include <future>
#include <iostream>
#include <kdbindings/signal.h>
#include <set>
#include <unordered_set>

namespace LaptimerCore::System
{

/**
 * Declaration of the FutureBaseWatcherBase class
 */
class FutureWatcherBase;

/**
 * FutureWatcher registry to emit signals in the context of the main loop.
 */
struct FutureRegistry
{
    void handleFutureWatcher() noexcept;
    void registerFutureWatcher(FutureWatcherBase *futureWatcher) noexcept;
    void deregisterFutureWatcher(FutureWatcherBase *futureWatcher) noexcept;
    std::unordered_map<FutureWatcherBase *, std::shared_ptr<std::atomic_bool>> futureRegistry{};
};

/**
 * Function that should be called periodically from the main loop to trigger signal handling.
 */
extern void handleFutureWatcher() noexcept;

/**
 * Abstract FutureWatcher base class
 */
class FutureWatcherBase
{
    friend struct FutureRegistry;

public:
    virtual ~FutureWatcherBase() noexcept = default;

    /**
     * Deleted copy constructor
     */
    FutureWatcherBase(const FutureWatcherBase &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    FutureWatcherBase &operator=(const FutureWatcherBase &other) = delete;

    /**
     * Deleted move constructor
     */
    FutureWatcherBase(FutureWatcherBase &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    FutureWatcherBase &operator=(FutureWatcherBase &&other) = delete;

    /**
     * This signal is emitted when the observed future execution is finished.
     */
    KDBindings::Signal<> finished;

    /**
     * Get the global FutureWatchRegistry
     * @return Gives the global FutureWatcher registry.
     */
    static FutureRegistry &getFutureRegisry();

protected:
    /**
     * Called periodically to check if the observed feature is done.
     */
    virtual void handleFinished() = 0;

    /**
     * Default constructor
     */
    FutureWatcherBase() = default;

    /**
     * Global registry in which the FutureWatcher are registered for signal handling.
     */
    static FutureRegistry registry; // NOLINT(*-avoid-non-const-global-variables)
};

template <class T>
class FutureWatcher : public FutureWatcherBase
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

        auto &registry = getFutureRegisry();
        if (registry.futureRegistry.count(this) > 0)
        {
            registry.deregisterFutureWatcher(this);
        }
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
        auto &registry = getFutureRegisry();
        registry.registerFutureWatcher(this);
        mFutureObserver = std::thread([this]() {
            mFuture.wait();
            *getFutureRegisry().futureRegistry.at(this) = true;
        });
    }

    /**
     * Gives the result of the future. If the still running the function will block and waits until the future is ready.
     * return The future result.
     * @return The Result of the underlying future.
     */
    [[nodiscard]] T getResult() noexcept
    {
        return mFuture.get();
    }

private:
    void handleFinished() override
    {
        finished.emit();
    }

    void futureWatcher() const noexcept
    {
        mFuture.wait();
    }

private:
    std::thread mFutureObserver;
    std::future<T> mFuture;
};

} // namespace LaptimerCore::System

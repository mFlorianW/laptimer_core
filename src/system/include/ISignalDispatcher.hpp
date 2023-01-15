#pragma once

#include <IDispatcherObject.hpp>

namespace LaptimerCore::System
{

/**
 * The ISignalDispatcher is used to dispatch signal of some system components in the right thread.
 */
class ISignalDispatcher
{
public:
    /**
     * Default destructor
     */
    virtual ~ISignalDispatcher() = default;

    /**
     * Deleted copy constructor
     */
    ISignalDispatcher(const ISignalDispatcher &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    ISignalDispatcher &operator=(const ISignalDispatcher &other) = delete;

    /**
     * Deleted move constructor
     */
    ISignalDispatcher(ISignalDispatcher &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    ISignalDispatcher &operator=(ISignalDispatcher &&other) = delete;

    /**
     * This function must be called periodically in the main loop or thread to dispatch the signals.
     */
    virtual void exec() noexcept = 0;

    /**
     * Register an object for signal dispatching.
     * @param timer that shall be registered.
     */
    virtual void registerObject(IDispatcherObject *obj) noexcept = 0;

    /**
     * Unregister an object from signal dispatching.
     * @param timer that shall be unregistered.
     */
    virtual void unregisterObject(IDispatcherObject *obj) noexcept = 0;

    /**
     * Gives the SignalDispatcher for the thread.
     * @return A SignalDispatcher for the thread.
     * @return A nullptr when no SignalDispatcher is present for the thread.
     */
    static ISignalDispatcher *getSignalDispatcher() noexcept;

protected:
    /**
     * Default constructor
     */
    ISignalDispatcher() = default;
};
} // namespace LaptimerCore::System

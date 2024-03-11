#pragma once

#include "IDispatcherObject.hpp"
#include "SystemTypes.hpp"
#include <thread>

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
    ISignalDispatcher(ISignalDispatcher const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    ISignalDispatcher& operator=(ISignalDispatcher const& other) = delete;

    /**
     * Deleted move constructor
     */
    ISignalDispatcher(ISignalDispatcher&& ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    ISignalDispatcher& operator=(ISignalDispatcher&& other) = delete;

    /**
     * This function must be called periodically in the main loop or thread to dispatch the signals.
     */
    virtual void exec() noexcept = 0;

    /**
     * Register an object for signal dispatching.
     * @param timer that shall be registered.
     */
    virtual Result registerObject(IDispatcherObject* obj, std::thread::id const& id) noexcept = 0;

    /**
     * Unregister an object from signal dispatching.
     * @param timer that shall be unregistered.
     */
    virtual Result unregisterObject(IDispatcherObject* obj, std::thread::id const& id) noexcept = 0;

    /**
     * Gives the SignalDispatcher for the thread if the functions returns a nullptr, that means that there
     * is no SignalDispatcher created for the thread where the function got called.
     * In that the case a SignalDispatcher instance must be created first. This behavior is on purpose so
     * you can not accidently call this function from the wrong thread.
     *
     * @return A SignalDispatcher for the thread.
     * @return A nullptr when no SignalDispatcher is present for the thread.
     */
    static ISignalDispatcher* getSignalDispatcher() noexcept;

protected:
    /**
     * Default constructor
     */
    ISignalDispatcher() = default;
};
} // namespace LaptimerCore::System

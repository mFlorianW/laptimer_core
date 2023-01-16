#pragma once
#include "ISignalDispatcher.hpp"
#include <thread>

namespace LaptimerCore::System
{

class SignalDispatcher : public ISignalDispatcher
{
public:
    /**
     * Default constructor
     */
    SignalDispatcher();

    /**
     * Default empty constructor
     */
    ~SignalDispatcher() override;

    /**
     * Deleted copy constructor
     */
    SignalDispatcher(const SignalDispatcher &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    SignalDispatcher &operator=(const SignalDispatcher &other) = delete;

    /**
     * Deleted move constructor
     */
    SignalDispatcher(SignalDispatcher &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    SignalDispatcher &operator=(SignalDispatcher &&other) = delete;

    /**
     * @copydoc ISignalDispatcher::exec()
     */
    void exec() noexcept override;

    /**
     * @copydoc ISignalDispatcher::registerObject()
     */
    Result registerObject(IDispatcherObject *obj, const std::thread::id &id) noexcept override;

    /**
     * @copydoc ISignalDispatcher::unregisterObject()
     */
    Result unregisterObject(IDispatcherObject *obj, const std::thread::id &id) noexcept override;

private:
    std::thread::id mThreadId;
};

} // namespace LaptimerCore::System

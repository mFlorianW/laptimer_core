#pragma once
#include "ISignalDispatcher.hpp"
#include "SystemTypes.hpp"

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
    void registerObject(IDispatcherObject *obj) noexcept override;

    /**
     * @copydoc ISignalDispatcher::unregisterObject()
     */
    void unregisterObject(IDispatcherObject *obj) noexcept override;
};

} // namespace LaptimerCore::System

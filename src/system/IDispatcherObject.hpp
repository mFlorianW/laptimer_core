#pragma once

namespace LaptimerCore::System
{

/**
 * A DispatcherObject is used to together with the ISignalDispatcher. This is the uniform interface between these
 * classes. The ISignalDispatcher calls dispatch to trigger the signal dispatching of the class if needed.
 */
class IDispatcherObject
{
public:
    virtual void dispatch() = 0;
};
} // namespace LaptimerCore::System

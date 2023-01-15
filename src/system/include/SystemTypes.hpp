#pragma once

#include "IDispatcherObject.hpp"
#include "ISignalDispatcher.hpp"
#include <unordered_set>

namespace LaptimerCore::System
{

struct SignalDispatcherContext
{
    SignalDispatcherContext(ISignalDispatcher *disp)
        : dispatcher{disp}
    {
    }

    ISignalDispatcher *dispatcher;
    std::unordered_set<IDispatcherObject *> objects;
};

} // namespace LaptimerCore::System

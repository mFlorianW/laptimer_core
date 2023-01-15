#include "ISignalDispatcher.hpp"
#include <SignalDispatcherRegistry.hpp>

namespace LaptimerCore::System
{
ISignalDispatcher *ISignalDispatcher::getSignalDispatcher() noexcept
{
    return SignalDispatcherRegistry::getInstance().getDispatcher(std::this_thread::get_id());
}
} // namespace LaptimerCore::System

#include "SignalDispatcher.hpp"
#include "SignalDispatcherRegistry.hpp"

namespace LaptimerCore::System
{

SignalDispatcher::SignalDispatcher()
    : ISignalDispatcher{}
{
    SignalDispatcherRegistry::getInstance().registerDispatcher(this, std::this_thread::get_id());
}

SignalDispatcher::~SignalDispatcher() = default;

void SignalDispatcher::exec() noexcept
{
    auto *context = SignalDispatcherRegistry::getInstance().getContext(std::this_thread::get_id());
    for (auto *obj : context->objects)
    {
        obj->dispatch();
    }
}

void SignalDispatcher::registerObject(IDispatcherObject *obj) noexcept
{
    if (obj != nullptr)
    {
        SignalDispatcherRegistry::getInstance().registerObject(obj, std::this_thread::get_id());
    }
}

void SignalDispatcher::unregisterObject(IDispatcherObject *obj) noexcept
{
    if (obj != nullptr)
    {
        SignalDispatcherRegistry::getInstance().unregisterObject(obj, std::this_thread::get_id());
    }
}

} // namespace LaptimerCore::System

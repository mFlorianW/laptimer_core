#include "SignalDispatcher.hpp"
#include "SignalDispatcherRegistry.hpp"
#include <iostream>

namespace LaptimerCore::System
{

SignalDispatcher::SignalDispatcher()
    : ISignalDispatcher{}
    , mThreadId{std::this_thread::get_id()}
{
    SignalDispatcherRegistry::getInstance().registerDispatcher(this, mThreadId);
}

SignalDispatcher::~SignalDispatcher() = default;

void SignalDispatcher::exec() noexcept
{
    if (mThreadId != std::this_thread::get_id())
    {
        std::cerr << "exec can only be called from the SignalDispatcher creation thread.\n";
        return;
    }

    auto *context = SignalDispatcherRegistry::getInstance().getContext(mThreadId);
    for (auto *obj : context->objects)
    {
        obj->dispatch();
    }
}

Result SignalDispatcher::registerObject(IDispatcherObject *obj, const std::thread::id &id) noexcept
{
    if ((obj != nullptr) && (mThreadId == id))
    {
        SignalDispatcherRegistry::getInstance().registerObject(obj, mThreadId);
        return Result::Ok;
    }
    std::cerr << "Objects can only be registered from the same thread as the SignalDispatcher\n";
    return Result::Error;
}

Result SignalDispatcher::unregisterObject(IDispatcherObject *obj, const std::thread::id &id) noexcept
{
    if ((obj != nullptr) && (mThreadId == id))
    {
        SignalDispatcherRegistry::getInstance().unregisterObject(obj, mThreadId);
        return Result::Ok;
    }
    std::cerr << "Objects can only be unregistered from the same thread as the SignalDispatcher\n";
    return Result::Error;
}

} // namespace LaptimerCore::System

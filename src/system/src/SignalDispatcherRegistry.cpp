#include "SignalDispatcherRegistry.hpp"

namespace LaptimerCore::System
{

SignalDispatcherRegistry &SignalDispatcherRegistry::getInstance() noexcept
{
    static SignalDispatcherRegistry registry;
    return registry;
}

RegisterResult SignalDispatcherRegistry::registerDispatcher(ISignalDispatcher *dispatcher,
                                                            const std::thread::id &id) noexcept
{
    auto contains = mContexts.find(id);
    if (contains != mContexts.end())
    {
        return RegisterResult::AlreadyRegistered;
    }

    mContexts.emplace(id, std::make_unique<SignalDispatcherContext>(dispatcher));
    return RegisterResult::Ok;
}

SignalDispatcherContext *SignalDispatcherRegistry::getContext(const std::thread::id &id) noexcept
{
    auto contains = mContexts.find(id);
    if (contains != mContexts.end())
    {
        const std::lock_guard<std::mutex> guard{mRegistryMutex};
        return mContexts.at(id).get();
    }
    else
    {
        return nullptr;
    }
}

ISignalDispatcher *SignalDispatcherRegistry::getDispatcher(const std::thread::id &id) noexcept
{
    const bool contains = mContexts.find(id) != mContexts.end();
    if (contains)
    {
        return mContexts.at(id)->dispatcher;
    }
    return nullptr;
}

void SignalDispatcherRegistry::registerObject(IDispatcherObject *obj, const std::thread::id &id) noexcept
{
    const bool contains = mContexts.find(id) != mContexts.end();
    if ((obj != nullptr) && contains)
    {
        const std::lock_guard<std::mutex> guard{mRegistryMutex};
        mContexts.at(id)->objects.insert(obj);
    }
}

void SignalDispatcherRegistry::unregisterObject(IDispatcherObject *obj, const std::thread::id &id) noexcept
{
    const bool contains = mContexts.find(id) != mContexts.end();
    if ((obj != nullptr) && contains)
    {
        const std::lock_guard<std::mutex> guard{mRegistryMutex};
        mContexts.at(id)->objects.erase(obj);
    }
}

} // namespace LaptimerCore::System

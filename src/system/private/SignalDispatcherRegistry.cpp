#include "SignalDispatcherRegistry.hpp"
#include <algorithm>

namespace LaptimerCore::System
{

SignalDispatcherRegistry &SignalDispatcherRegistry::getInstance() noexcept
{
    static SignalDispatcherRegistry registry;
    return registry;
}

Result SignalDispatcherRegistry::registerDispatcher(ISignalDispatcher *dispatcher, const std::thread::id &id) noexcept
{
    auto contains = mContexts.find(id);
    if (contains != mContexts.end())
    {
        return Result::Error;
    }

    mContexts.emplace(id, std::make_unique<SignalDispatcherContext>(dispatcher));
    return Result::Ok;
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
        mContexts.at(id)->objects.push_back(obj);
    }
}

void SignalDispatcherRegistry::unregisterObject(IDispatcherObject *obj, const std::thread::id &id) noexcept
{
    const bool contains = mContexts.find(id) != mContexts.end();
    if ((obj != nullptr) && contains)
    {
        const std::lock_guard<std::mutex> guard{mRegistryMutex};
        auto &objects = mContexts.at(id)->objects;
        auto objPos = std::find(objects.begin(), objects.end(), obj);
        if (objPos != objects.end())
        {
            mContexts.at(id)->objects.erase(objPos);
        }
    }
}

} // namespace LaptimerCore::System
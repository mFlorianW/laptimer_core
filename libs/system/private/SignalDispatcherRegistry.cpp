// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SignalDispatcherRegistry.hpp"
#include <algorithm>

namespace LaptimerCore::System
{

SignalDispatcherRegistry& SignalDispatcherRegistry::getInstance() noexcept
{
    static SignalDispatcherRegistry registry;
    return registry;
}

Result SignalDispatcherRegistry::registerDispatcher(ISignalDispatcher* dispatcher, std::thread::id const& id) noexcept
{
    auto contains = mContexts.find(id);
    if (contains != mContexts.end()) {
        return Result::Error;
    }

    mContexts.emplace(id, std::make_unique<SignalDispatcherContext>(dispatcher));
    return Result::Ok;
}

SignalDispatcherContext* SignalDispatcherRegistry::getContext(std::thread::id const& id) noexcept
{
    auto contains = mContexts.find(id);
    if (contains != mContexts.end()) {
        std::lock_guard<std::mutex> const guard{mRegistryMutex};
        return mContexts.at(id).get();
    } else {
        return nullptr;
    }
}

ISignalDispatcher* SignalDispatcherRegistry::getDispatcher(std::thread::id const& id) noexcept
{
    bool const contains = mContexts.find(id) != mContexts.end();
    if (contains) {
        return mContexts.at(id)->dispatcher;
    }
    return nullptr;
}

void SignalDispatcherRegistry::registerObject(IDispatcherObject* obj, std::thread::id const& id) noexcept
{
    bool const contains = mContexts.find(id) != mContexts.end();
    if ((obj != nullptr) && contains) {
        std::lock_guard<std::mutex> const guard{mRegistryMutex};
        mContexts.at(id)->objects.push_back(obj);
    }
}

void SignalDispatcherRegistry::unregisterObject(IDispatcherObject* obj, std::thread::id const& id) noexcept
{
    bool const contains = mContexts.find(id) != mContexts.end();
    if ((obj != nullptr) && contains) {
        std::lock_guard<std::mutex> const guard{mRegistryMutex};
        auto& objects = mContexts.at(id)->objects;
        auto objPos = std::find(objects.begin(), objects.end(), obj);
        if (objPos != objects.end()) {
            mContexts.at(id)->objects.erase(objPos);
        }
    }
}

} // namespace LaptimerCore::System

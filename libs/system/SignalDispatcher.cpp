// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SignalDispatcher.hpp"
#include "private/SignalDispatcherRegistry.hpp"
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
    if (mThreadId != std::this_thread::get_id()) {
        std::cerr << "exec can only be called from the SignalDispatcher creation thread.\n";
        return;
    }

    auto& context = SignalDispatcherRegistry::getInstance().getContext(mThreadId)->objects;
    for (auto& obj : context) {
        if (!context.empty()) {
            obj->dispatch();
        }
    }
}

Result SignalDispatcher::registerObject(IDispatcherObject* obj, std::thread::id const& id) noexcept
{
    if ((obj != nullptr) && (mThreadId == id)) {
        SignalDispatcherRegistry::getInstance().registerObject(obj, mThreadId);
        return Result::Ok;
    }
    std::cerr << "Objects can only be registered from the same thread as the SignalDispatcher\n";
    return Result::Error;
}

Result SignalDispatcher::unregisterObject(IDispatcherObject* obj, std::thread::id const& id) noexcept
{
    if ((obj != nullptr) && (mThreadId == id)) {
        SignalDispatcherRegistry::getInstance().unregisterObject(obj, id);
        return Result::Ok;
    }
    std::cerr << "Objects can only be unregistered from the same thread as the SignalDispatcher\n";
    return Result::Error;
}

} // namespace LaptimerCore::System

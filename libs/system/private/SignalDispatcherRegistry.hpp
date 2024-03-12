// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "DispatcherTypes.hpp"
#include "ISignalDispatcher.hpp"
#include <mutex>
#include <thread>
#include <unordered_map>

namespace LaptimerCore::System
{

class SignalDispatcherRegistry
{
public:
    static SignalDispatcherRegistry& getInstance() noexcept;

    Result registerDispatcher(ISignalDispatcher* dispatcher, std::thread::id const& id) noexcept;

    SignalDispatcherContext* getContext(std::thread::id const& id) noexcept;

    ISignalDispatcher* getDispatcher(std::thread::id const& id) noexcept;

    void registerObject(IDispatcherObject* obj, std::thread::id const& id) noexcept;

    void unregisterObject(IDispatcherObject* obj, std::thread::id const& id) noexcept;

private:
    std::unordered_map<std::thread::id, std::unique_ptr<SignalDispatcherContext>> mContexts{};
    std::mutex mutable mRegistryMutex;
};

}; // namespace LaptimerCore::System

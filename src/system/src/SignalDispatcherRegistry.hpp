#pragma once

#include "ISignalDispatcher.hpp"
#include "SystemTypes.hpp"
#include <mutex>
#include <thread>
#include <unordered_map>

namespace LaptimerCore::System
{
enum class RegisterResult
{
    Ok,
    AlreadyRegistered,
};

class SignalDispatcherRegistry
{
public:
    static SignalDispatcherRegistry &getInstance() noexcept;

    RegisterResult registerDispatcher(ISignalDispatcher *dispatcher, const std::thread::id &id) noexcept;

    SignalDispatcherContext *getContext(const std::thread::id &id) noexcept;

    ISignalDispatcher *getDispatcher(const std::thread::id &id) noexcept;

    void registerObject(IDispatcherObject *obj, const std::thread::id &id) noexcept;

    void unregisterObject(IDispatcherObject *obj, const std::thread::id &id) noexcept;

private:
    std::unordered_map<std::thread::id, std::unique_ptr<SignalDispatcherContext>> mContexts{};
    std::mutex mutable mRegistryMutex;
};

}; // namespace LaptimerCore::System

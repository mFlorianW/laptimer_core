#include "FutureWatcher.hpp"

namespace LaptimerCore::System
{

FutureRegistry FutureWatcherBase::registry = FutureRegistry{}; // NOLINT(*-avoid-non-const-global-variables)

FutureRegistry &FutureWatcherBase::getFutureRegisry()
{
    return FutureWatcherBase::registry;
}

void FutureRegistry::registerFutureWatcher(FutureWatcherBase *futureWatcher) noexcept
{
    futureRegistry.emplace(futureWatcher, std::make_shared<std::atomic_bool>(false));
}

void FutureRegistry::deregisterFutureWatcher(FutureWatcherBase *futureWatcher) noexcept
{
    if (futureRegistry.count(futureWatcher) > 0)
    {
        futureRegistry.erase(futureWatcher);
    }
}

void FutureRegistry::handleFutureWatcher() noexcept
{
    for (const auto &[futureWatcher, finish] : futureRegistry)
    {
        if (*finish)
        {
            futureWatcher->handleFinished();
        }
    }
}

void handleFutureWatcher() noexcept
{
    FutureWatcherBase::getFutureRegisry().handleFutureWatcher();
}

} // namespace LaptimerCore::System

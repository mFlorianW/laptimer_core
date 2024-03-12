// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ISignalDispatcher.hpp"
#include "private/SignalDispatcherRegistry.hpp"

namespace LaptimerCore::System
{
ISignalDispatcher* ISignalDispatcher::getSignalDispatcher() noexcept
{
    return SignalDispatcherRegistry::getInstance().getDispatcher(std::this_thread::get_id());
}
} // namespace LaptimerCore::System

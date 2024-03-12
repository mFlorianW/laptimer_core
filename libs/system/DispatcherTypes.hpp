// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ISignalDispatcher.hpp"
#include <vector>

namespace LaptimerCore::System
{

struct SignalDispatcherContext
{
    SignalDispatcherContext(ISignalDispatcher* disp)
        : dispatcher{disp}
    {
    }

    ISignalDispatcher* dispatcher;
    std::vector<IDispatcherObject*> objects;
};

} // namespace LaptimerCore::System

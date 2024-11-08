// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "QEventDispatcher.hpp"
#include <QDebug>

namespace Rapid::System::Qt
{

bool QEventDispatcher::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    mEventLoop.processEvents();
    return QPAEventDispatcherGlib::processEvents(flags);
}

} // namespace Rapid::System::Qt

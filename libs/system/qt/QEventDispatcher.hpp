// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "EventLoop.hpp"
#include <QtGui/private/qeventdispatcher_glib_p.h>

namespace Rapid::System::Qt
{

/**
 * Custom QAbstractEventDispatcher that processes events from @ref Rapid::System::EventLoop before
 * the Qt events.
 * That makes it possible to use the @ref Rapid::System::EventLoop based classes in Qt Application.
 */
class QEventDispatcher : public QPAEventDispatcherGlib
{
public:
    /**
     * Overwritten function that calls automatically Rapid::System::EventLoop::processEvents.
     * @param flags The flags of Qt which kind of Events shall be processed.
     * @return The return value of the base class implementation of QPAEventDispatcherGlib.
     */
    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;

private:
    EventLoop mEventLoop;
};

} // namespace Rapid::System::Qt

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "Event.hpp"

namespace LaptimerCore::System
{

Event::Event(Type type)
    : mEventType{type}
{
}

Event::~Event() noexcept = default;

Event::Type Event::getEventType() const noexcept
{
    return mEventType;
}

} // namespace LaptimerCore::System

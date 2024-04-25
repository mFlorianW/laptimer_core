// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "Event.hpp"
#include <thread>

namespace LaptimerCore::System
{

class EventReceiver
{
public:
    virtual ~EventReceiver() = default;
    virtual bool handleEvent(Event* event) = 0;
    std::thread::id getThreadId() const noexcept
    {
        return mThreadId;
    }

protected:
    EventReceiver()
        : mThreadId{std::this_thread::get_id()}
    {
    }

private:
    std::thread::id mThreadId = std::thread::id{0};
};

} // namespace LaptimerCore::System

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "Timer.hpp"

namespace LaptimerCore::System::Private
{

class TimerImpl
{
public:
    explicit TimerImpl(Timer& timer) noexcept;
    ~TimerImpl() noexcept;

    TimerImpl(TimerImpl const&) = delete;
    TimerImpl& operator=(TimerImpl const&) = delete;

    TimerImpl(TimerImpl&&) = delete;
    TimerImpl& operator=(TimerImpl&&) = delete;

    void setTimerInterval(std::chrono::nanoseconds interval) noexcept;

private:
    bool mInitialized = false;
    Timer& mTimer;
    timer_t mTimerId{nullptr};
};

} // namespace LaptimerCore::System::Private

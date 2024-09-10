// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "BoostTimer.hpp"
#include "EventLoop.hpp"

namespace LaptimerCore::System::Private
{

TimerImpl::TimerImpl(Timer& timer)
    : mTimer{timer}
{
}

TimerImpl::~TimerImpl() noexcept
{
    mTimerThread.join();
}

void TimerImpl::setTimerInterval(std::chrono::nanoseconds interval) noexcept
{
    mInterval = interval;
    if (interval.count() > 0) {
        mTimerThread = std::thread{[this]() {
            setupTimer();
        }};
    } else {
        mIoContext.stop();
    }
}

void TimerImpl::onTimeout(boost::system::error_code const& errorCode)
{
    // This function is called from the mTimerThread so here we don't need to start a new thread.
    // As long as the interval is greater than 0 the timer will be restarted.
    EventLoop::postEvent(&mTimer, std::make_unique<Event>(Event::Type::Timeout));
    if (mInterval.count() > 0) {
        setupTimer();
    }
}

void TimerImpl::setupTimer()
{
    mBoostTimer.expires_from_now(mInterval);
    mBoostTimer.async_wait([this](boost::system::error_code const& errorCode) {
        onTimeout(errorCode);
    });
    mIoContext.run();
}

} // namespace LaptimerCore::System::Private

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "BoostTimer.hpp"
#include "EventLoop.hpp"
#include <iostream>
#include <memory>

namespace Rapid::System::Private
{

TimerImpl::TimerImpl(Timer& timer)
    : mTimer{timer}
{
}

TimerImpl::~TimerImpl() noexcept
{
    mTimerActive = false;
    if (mTimerThread.joinable()) {
        mTimerThread.join();
    }
}

void TimerImpl::setTimerInterval(std::chrono::nanoseconds interval) noexcept
{
    mInterval = interval;
    if (interval.count() > 0) {
        mTimerActive = true;
        try {
            setupTimer();
            mTimerThread = std::thread{[this]() {
                while (mTimerActive) {
                    mIoContext.run();
                }
            }};
        } catch (std::system_error const& e) {
            std::cerr << "Failed to created timer thread for timer: " << std::addressof(mTimer) << " Error:" << e.what()
                      << "\n";
            return;
        } catch (boost::system::system_error const& e) {
            std::cerr << "Failed to setup timer for timer: " << std::addressof(mTimer) << " Error:" << e.what() << "\n";
            return;
        } catch (std::exception const& e) {
            std::cerr << "Unknown error:" << e.what() << "\n";
            return;
        }
    } else {
        mTimerActive = false;
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
}

} // namespace Rapid::System::Private

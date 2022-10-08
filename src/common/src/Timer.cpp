#include "Timer.hpp"
#include <unordered_set>

namespace LaptimerCore::Common
{

struct TimerRegister
{
    std::unordered_set<Timer *> timers;

    void handleAllTimerTicks()
    {
        for (const auto &timer : timers)
        {
            if (timer->isRunning())
            {
                timer->handleTicks();
            }
        }
    }
};

namespace
{
auto s_timers = TimerRegister{};
} // namespace

void handleTimerTicks()
{
    s_timers.handleAllTimerTicks();
}

Timer::Timer()
{
    s_timers.timers.insert(this);
}

Timer::~Timer()
{
    if (mRunning)
    {
        stop();
    }
    s_timers.timers.erase(this);
}

void Timer::start()
{
    if (mRunning || (mInterval == std::chrono::milliseconds(0)))
    {
        return;
    }

    mStartTime = std::chrono::steady_clock::now();
    mRunning = true;
}

void Timer::stop()
{
    mRunning = false;
}

void Timer::setInterval(std::chrono::milliseconds interval)
{
    mInterval = interval;
    if (mRunning)
    {
        stop();
        start();
    }
}

std::chrono::milliseconds Timer::getInterval()
{
    return mInterval;
}

bool Timer::isRunning()
{
    return mRunning;
}

void Timer::handleTicks()
{
    const auto elapsedTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mStartTime).count();
    if (elapsedTime >= mInterval.count())
    {
        mStartTime = std::chrono::steady_clock::now();
        timeout.emit();
    }
}

} // namespace LaptimerCore::Common

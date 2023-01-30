#include "Timer.hpp"
#include "SignalDispatcher.hpp"
#include <unordered_set>

namespace LaptimerCore::System
{

Timer::Timer()
{
    SignalDispatcher{}.registerObject(this, std::this_thread::get_id());
}

Timer::~Timer()
{
    if (mRunning)
    {
        stop();
    }

    SignalDispatcher{}.unregisterObject(this, std::this_thread::get_id());
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

void Timer::dispatch()
{
    if (mRunning)
    {
        const auto elapsedTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mStartTime)
                .count();
        if (elapsedTime >= mInterval.count())
        {
            mStartTime = std::chrono::steady_clock::now();
            timeout.emit();
        }
    }
}

} // namespace LaptimerCore::System

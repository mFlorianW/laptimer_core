#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <kdbindings/signal.h>

namespace LaptimerCore::Common
{
/**
 * This function must be called frequently in the main loop,
 * to update the timeout intervals.
 */
extern void handleTimerTicks();

class Timer final
{
    friend struct TimerRegister;

public:
    /**
     * Creates an instance of the Timer.
     */
    Timer();

    ~Timer();

    /**
     * Starts the timer. The timer sends the timeout signal when the set interval is reached.
     */
    void start();

    /**
     * Stops the timer.
     */
    void stop();

    /**
     * Sets the interval for the timer.
     * Setting the interval for a already running timer, stops and starts the timer again with the new interval.
     */
    void setInterval(std::chrono::milliseconds interval);

    /**
     * Gives the interval of the timer.
     * @return Gives the interval of the timer.
     */
    std::chrono::milliseconds getInterval();

    /**
     * Gives the state of the timer is it running or not.
     * @return True means the timer is running, false means is not.
     */
    bool isRunning();

    /**
     * This signal is emitted when the timer reaches it's intervall.
     */
    KDBindings::Signal<> timeout;

private:
    void handleTicks();

private:
    std::chrono::milliseconds mInterval{0};
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    bool mRunning{false};
};

} // namespace LaptimerCore::Common

#endif // TIMER_HPP

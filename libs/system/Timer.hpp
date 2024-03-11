#ifndef TIMER_HPP
#define TIMER_HPP

#include "IDispatcherObject.hpp"
#include <chrono>
#include <kdbindings/signal.h>

namespace LaptimerCore::System
{

class Timer final : public IDispatcherObject
{
    friend struct TimerRegister;

public:
    /**
     * Creates an instance of the Timer.
     */
    Timer();

    /**
     * Default destructor
     */
    ~Timer() override;

    /**
     * Deleted copy constructor
     */
    Timer(Timer const& other) = delete;

    /**
     * Deleted copy operator
     */
    Timer& operator=(Timer const& other) = delete;

    /**
     * Deleted move constructor
     */
    Timer(Timer&& other) = delete;

    /**
     * Deleted move operator
     */
    Timer& operator=(Timer&& other) = delete;

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

protected:
    void dispatch() override;

private:
    std::chrono::milliseconds mInterval{0};
    std::chrono::time_point<std::chrono::steady_clock> mStartTime;
    bool mRunning{false};
};

} // namespace LaptimerCore::System

#endif // TIMER_HPP

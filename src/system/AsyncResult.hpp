#pragma once

#include "SystemTypes.hpp"
#include <kdbindings/signal.h>

namespace LaptimerCore::System
{

/**
 * An AsyncResult is a result object for asynchronous operations. The done signal is used as indication that the
 * operation is finshed. The Result must be inherited for the conrect use case. The result must be set with
 * the protected function: @AsyncResult::setResult().
 */
class AsyncResult
{
public:
    /**
     * Creates an Instance of AsyncResult
     */
    AsyncResult();

    /**
     * Destructor
     */
    virtual ~AsyncResult();

    /**
     * Deleted copy constructor
     */
    AsyncResult(const AsyncResult &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    AsyncResult &operator=(const AsyncResult &other) = delete;

    /**
     * Move constructor
     */
    AsyncResult(AsyncResult &&ohter) noexcept;

    /**
     * Move assignemnt operator
     */
    AsyncResult &operator=(AsyncResult &&other) noexcept;

    /**
     * Gives the result. The result is not valid (@Result::NotFinshed) as long as the or the
     * @AsyncResult::finished is emitted.
     * @return The asynchronous result
     */
    Result getResult() const noexcept;

    /**
     * Gives the error message of the result. If no error message exists then the
     * string is empty.
     * @return The error message.
     */
    std::string_view getErrorMessage() const noexcept;

    /**
     * Blocks until the async result is there and suspends the current running thread.
     * The function periodically calls the SignalDispatcher for the thread.
     */
    void waitForFinished() noexcept;

    /**
     * The done signal is emitted when the async operation is finished.
     * @param The signal contains a pointer to Async instance for directly requesting the
     * result in the slot.
     */
    KDBindings::Signal<AsyncResult *> done;

protected:
    /**
     * Set the result of the AsyncResult and emits the @AsyncResult::finished signal
     * @result The result state of the AsyncResult
     * @errorMessage Sets an optional error message
     */
    void setResult(Result result, const std::string &errorMessage = {}) noexcept;

private:
    Result mResult{Result::NotFinished};
    std::string mErrorMsg{};
};
} // namespace LaptimerCore::System

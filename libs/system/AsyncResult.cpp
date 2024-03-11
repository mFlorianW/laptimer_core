#include "AsyncResult.hpp"
#include "SignalDispatcher.hpp"

namespace LaptimerCore::System
{

AsyncResult::AsyncResult() = default;
AsyncResult::~AsyncResult() = default;
AsyncResult::AsyncResult(AsyncResult&& other) noexcept = default;
AsyncResult& AsyncResult::operator=(AsyncResult&& other) noexcept = default;

Result AsyncResult::getResult() const noexcept
{
    return mResult;
}

std::string_view AsyncResult::getErrorMessage() const noexcept
{
    return mErrorMsg;
}

void AsyncResult::waitForFinished() noexcept
{
    if (mResult != Result::NotFinished) {
        return;
    }

    auto disp = SignalDispatcher{};
    while (mResult == Result::NotFinished) {
        disp.exec();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void AsyncResult::setResult(Result result, std::string const& errorMessage) noexcept
{
    mResult = result;
    mErrorMsg = errorMessage;
    done.emit(this);
}

} // namespace LaptimerCore::System

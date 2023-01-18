#include "AsyncResult.hpp"

namespace LaptimerCore::System
{

AsyncResult::AsyncResult() = default;
AsyncResult::~AsyncResult() = default;
AsyncResult::AsyncResult(AsyncResult &&other) noexcept = default;
AsyncResult &AsyncResult::operator=(AsyncResult &&other) noexcept = default;

Result AsyncResult::getResult() const noexcept
{
    return mResult;
}

std::string_view AsyncResult::getErrorMessage() const noexcept
{
    return mErrorMsg;
}

void AsyncResult::setResult(Result result, const std::string &errorMessage) noexcept
{
    mResult = result;
    mErrorMsg = errorMessage;
    done.emit(this);
}

} // namespace LaptimerCore::System

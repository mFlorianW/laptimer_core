#include "RestCall.hpp"

namespace LaptimerCore::Rest
{

bool RestCall::isFinished() const noexcept
{
    return mResult != RestCallResult::Unknown;
}

RestCallResult RestCall::getResult() const noexcept
{
    return mResult;
}

std::string RestCall::getData() const noexcept
{
    return mRawData;
}

void RestCall::setData(const std::string &data) noexcept
{
    mRawData = data;
}

} // namespace LaptimerCore::Rest

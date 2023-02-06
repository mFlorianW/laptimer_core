#include "RestRequest.hpp"
#include <string>

namespace LaptimerCore::Rest
{
struct SharedRestRequest : public Common::SharedData
{
    std::string mRequestBody;

    friend bool operator==(const SharedRestRequest &lhs, const SharedRestRequest &rhs)
    {
        return lhs.mRequestBody == rhs.mRequestBody;
    }
};

RestRequest::RestRequest() noexcept
    : mData{new(std::nothrow) SharedRestRequest{}}
{
}

RestRequest::~RestRequest() noexcept = default;

std::string_view RestRequest::getRequestBody() const noexcept
{
    return mData->mRequestBody;
}

void RestRequest::setRequestBody(const std::string &requestBody) noexcept
{
    mData->mRequestBody = requestBody;
}

bool operator==(const RestRequest &lhs, const RestRequest &rhs) noexcept
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(const RestRequest &lhs, const RestRequest &rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Rest

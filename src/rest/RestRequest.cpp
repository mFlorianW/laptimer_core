#include "RestRequest.hpp"
#include <string>

namespace LaptimerCore::Rest
{
struct SharedRestRequest : public Common::SharedData
{
    Path mRequestPath;
    std::string mRequestBody;
    std::string mReturnBody;

    friend bool operator==(const SharedRestRequest &lhs, const SharedRestRequest &rhs)
    {
        return (lhs.mRequestBody == rhs.mRequestBody) && (lhs.mReturnBody == rhs.mReturnBody) &&
               (lhs.mRequestPath == rhs.mRequestPath);
    }
};

RestRequest::RestRequest(std::string requestPath, std::string requestBody) noexcept
    : mData{new(std::nothrow) SharedRestRequest{}}
{
    mData->mRequestBody = std::move(requestBody);
    mData->mRequestPath = Path{std::move(requestPath)};
}

RestRequest::~RestRequest() noexcept = default;

std::string_view RestRequest::getRequestBody() const noexcept
{
    return mData->mRequestBody;
}

Path RestRequest::getPath() const noexcept
{
    return mData->mRequestPath;
}

std::string RestRequest::getReturnBody() const noexcept
{
    return mData->mReturnBody;
}

void RestRequest::setReturnBody(const std::string &returnBody) noexcept
{
    mData->mReturnBody = returnBody;
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

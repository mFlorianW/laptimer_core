#include "RestRequest.hpp"
#include <string>

namespace LaptimerCore::Rest
{
struct SharedRestRequest : public Common::SharedData
{
    Path mRequestPath;
    std::string mRequestBody;
    std::string mReturnBody;
    RequestType mType{};

    friend bool operator==(SharedRestRequest const& lhs, SharedRestRequest const& rhs)
    {
        return (lhs.mRequestBody == rhs.mRequestBody) && (lhs.mReturnBody == rhs.mReturnBody) &&
               (lhs.mRequestPath == rhs.mRequestPath) && (lhs.mType == rhs.mType);
    }
};

RestRequest::RestRequest() noexcept
    : mData{new(std::nothrow) SharedRestRequest{}}
{
}

RestRequest::RestRequest(RequestType type, std::string requestPath, std::string requestBody) noexcept
    : mData{new(std::nothrow) SharedRestRequest{}}
{
    mData->mType = type;
    mData->mRequestBody = std::move(requestBody);
    mData->mRequestPath = Path{std::move(requestPath)};
}

RestRequest::~RestRequest() noexcept = default;
RestRequest::RestRequest(RestRequest const& other) noexcept = default;
RestRequest& RestRequest::operator=(RestRequest const& other) noexcept = default;
RestRequest::RestRequest(RestRequest&& other) noexcept = default;
RestRequest& RestRequest::operator=(RestRequest&& other) noexcept = default;

RequestType RestRequest::getType() const noexcept
{
    return mData->mType;
}

std::string_view RestRequest::getRequestBody() const noexcept
{
    return mData->mRequestBody;
}

Path RestRequest::getPath() const noexcept
{
    return mData->mRequestPath;
}

std::string_view RestRequest::getReturnBody() const noexcept
{
    return mData->mReturnBody;
}

void RestRequest::setReturnBody(std::string const& returnBody) noexcept
{
    mData->mReturnBody = returnBody;
}

bool operator==(RestRequest const& lhs, RestRequest const& rhs) noexcept
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(RestRequest const& lhs, RestRequest const& rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Rest

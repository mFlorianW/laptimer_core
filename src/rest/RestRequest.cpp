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

RestRequest::RestRequest(const std::string &rawData) noexcept
    : mData{new(std::nothrow) SharedRestRequest{}}
{
    mData->mRequestBody = rawData;
}

RestRequest::~RestRequest() noexcept = default;

std::string_view RestRequest::getRequestBody() const noexcept
{
    return mData->mRequestBody;
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

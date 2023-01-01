#include "RestRequest.hpp"
#include <string>

namespace LaptimerCore::Rest
{
struct SharedRestRequest : public Common::SharedData
{
    std::string mRawData;

    friend bool operator==(const SharedRestRequest &lhs, const SharedRestRequest &rhs)
    {
        return lhs.mRawData == rhs.mRawData;
    }
};

RestRequest::RestRequest(const std::string &rawData) noexcept
    : mData{new (std::nothrow) SharedRestRequest{}}
{
    mData->mRawData = rawData;
}

RestRequest::~RestRequest() noexcept = default;
RestRequest::RestRequest(const RestRequest &other) noexcept = default;
RestRequest &RestRequest::operator=(const RestRequest &other) noexcept = default;
RestRequest::RestRequest(RestRequest &&other) noexcept = default;
RestRequest &RestRequest::operator=(RestRequest &&other) noexcept = default;

std::string_view RestRequest::getRawData() const noexcept
{
    return mData->mRawData;
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

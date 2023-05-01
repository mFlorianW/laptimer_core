#include "RestSessionDownloaderClient.hpp"

namespace LaptimerCore::TestHelper
{

class TestRestCall : public Rest::RestCall
{
public:
    void setCallResult(Rest::RestCallResult result) noexcept override
    {
        mResult = result;
        finished.emit(this);
    }
};

void RestSessionDownloaderClient::setServerAddress(const std::string &address) noexcept
{
}

void RestSessionDownloaderClient::setServerPort(std::uint16_t port) noexcept
{
}

std::shared_ptr<Rest::RestCall> RestSessionDownloaderClient::execute(const Rest::RestRequest &request) noexcept
{
    mLastRequest = request;
    auto call = std::make_shared<TestRestCall>();
    if (request.getPath().getPath() == "/sessions")
    {
        call->setData({R"({"count":2})"});
    }
    call->setCallResult(Rest::RestCallResult::Success);
    return call;
}

} // namespace LaptimerCore::TestHelper

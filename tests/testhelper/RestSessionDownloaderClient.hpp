#pragma once
#include "IRestClient.hpp"
#include "RestRequest.hpp"

namespace LaptimerCore::TestHelper
{
class RestSessionDownloaderClient : public Rest::IRestClient
{
    void setServerAddress(const std::string &address) noexcept override;

    void setServerPort(std::uint16_t port) noexcept override;

    std::shared_ptr<Rest::RestCall> execute(const Rest::RestRequest &request) noexcept override;

    Rest::RestRequest mLastRequest;
};
} // namespace LaptimerCore::TestHelper

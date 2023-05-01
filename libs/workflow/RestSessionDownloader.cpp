#include "RestSessionDownloader.hpp"
#include <ArduinoJson.hpp>
#include <iostream>

namespace LaptimerCore::Workflow
{

RestSessionDownloader::RestSessionDownloader(Rest::IRestClient &restClient) noexcept
    : ISessionDownloader()
    , mRestClient{restClient}
{
}

std::size_t RestSessionDownloader::getSessionCount() const noexcept
{
    return mSessionCount;
}

void RestSessionDownloader::fetchSessionCount() noexcept
{
    auto call = mRestClient.execute(Rest::RestRequest{Rest::RequestType::Get, "/sessions"});
    mFetchCounterCache.insert({call.get(), call});
    if (call->isFinished())
    {
        fetchSessionCountFinished(call.get());
    }
    else
    {
        call->finished.connect(&RestSessionDownloader::fetchSessionCountFinished, this);
    }
}

std::optional<Common::SessionData> RestSessionDownloader::getSession(std::size_t index) const noexcept
{
    return std::nullopt;
}

void RestSessionDownloader::downloadSession(std::size_t index) noexcept
{
}

void RestSessionDownloader::fetchSessionCountFinished(Rest::RestCall *call) noexcept
{
    if (mFetchCounterCache.count(call) > 0)
    {
        const auto dlResult =
            call->getResult() == Rest::RestCallResult::Success ? DownloadResult::Ok : DownloadResult::Error;
        if (dlResult == DownloadResult::Ok)
        {
            auto jsonDoc = ArduinoJson::DynamicJsonDocument{256};
            const auto error = ArduinoJson::deserializeJson(jsonDoc, call->getData());
            if (error != ArduinoJson::DeserializationError::Ok)
            {
                std::cout << "RestSessionDownloader Error: DeserializeJson failed: " << error.c_str() << "\n";
            }
            mSessionCount = jsonDoc["count"].as<std::size_t>();
        }
        sessionCountFetched.emit(dlResult);
    }
}
} // namespace LaptimerCore::Workflow

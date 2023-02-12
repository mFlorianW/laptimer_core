#include "SessionEndpoint.hpp"
#include <ArduinoJson.hpp>
#include <JsonSerializer.hpp>
#include <charconv>

namespace LaptimerCore::Rest
{

SessionEndpoint::SessionEndpoint(Storage::ISessionDatabase &database) noexcept
    : mDb{database}
{
}

RequestHandleResult SessionEndpoint::handleRestRequest(RestRequest &request) noexcept
{
    constexpr auto endpointIdentifier = "sessions";
    if ((request.getPath().getDepth() == 1) && (request.getPath().getEntry(0) == endpointIdentifier))
    {
        auto responsebody = ArduinoJson::DynamicJsonDocument{64};
        responsebody["count"] = mDb.getSessionCount();
        auto rawBody = std::string{};
        ArduinoJson::serializeJson(responsebody, rawBody);
        request.setReturnBody(rawBody);
        return RequestHandleResult::Ok;
    }
    else if ((request.getPath().getDepth() == 2) && (request.getPath().getEntry(0) == endpointIdentifier))
    {
        auto sessionId = std::size_t{0};
        const auto idString = request.getPath().getEntry(1).value_or("");
        const auto result = std::from_chars(idString.cbegin(), idString.cend(), sessionId);
        if (result.ec == std::errc::invalid_argument)
        {
            return RequestHandleResult::Error;
        }

        const auto session = mDb.getSessionByIndex(sessionId);
        if (!session.has_value())
        {
            return RequestHandleResult::Error;
        }

        auto responsebody = ArduinoJson::DynamicJsonDocument{8192};
        auto jsonRoot = responsebody.to<ArduinoJson::JsonObject>();
        Common::JsonSerializer::serializeSessionData(session.value(), jsonRoot);
        auto rawBody = std::string{};
        ArduinoJson::serializeJson(responsebody, rawBody);
        request.setReturnBody(rawBody);
        return RequestHandleResult::Ok;
    }

    return RequestHandleResult::Error;
}

} // namespace LaptimerCore::Rest

#include "SessionDatabase.hpp"
#include "JsonSerializer.hpp"

namespace LaptimerCore::Session
{

SessionDatabase::SessionDatabase(ISessionDatabaseBackend &backend)
    : mBackend{backend}
{
}

SessionDatabase::~SessionDatabase() = default;

std::size_t SessionDatabase::getSessionCount()
{
    return 0;
}

std::optional<LaptimerCore::Common::SessionData> SessionDatabase::getSessionByIndex(std::size_t index) const noexcept
{
    return std::nullopt;
}

bool SessionDatabase::storeSession(const Common::SessionData &session)
{
    ArduinoJson::StaticJsonDocument<8192> jsonDoc;
    auto jsonRootObject = jsonDoc.to<ArduinoJson::JsonObject>();
    Common::JsonSerializer::serializeSessionData(session, jsonRootObject);

    auto index = mBackend.getLastStoredIndex() + 1;

    return mBackend.storeSession(index, jsonDoc.as<std::string>());
}

} // namespace LaptimerCore::Session

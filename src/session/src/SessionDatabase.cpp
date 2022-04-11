#include "SessionDatabase.hpp"
#include "JsonDeserializer.hpp"
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
    return mBackend.getNumberOfStoredSessions();
}

std::optional<LaptimerCore::Common::SessionData> SessionDatabase::getSessionByIndex(std::size_t index) const noexcept
{
    const auto rawSession = mBackend.loadSessionByIndex(index);
    if (rawSession.empty())
    {
        return std::nullopt;
    }

    auto sessionData = Common ::JsonDeserializer::deserializeSessionData(rawSession);
    if (!sessionData)
    {
        return std::nullopt;
    }

    return sessionData;
}

bool SessionDatabase::storeSession(const Common::SessionData &session)
{
    ArduinoJson::StaticJsonDocument<8192> jsonDoc;
    auto jsonRootObject = jsonDoc.to<ArduinoJson::JsonObject>();
    Common::JsonSerializer::serializeSessionData(session, jsonRootObject);

    auto index = mBackend.getIndexList().empty() ? 0 : mBackend.getLastStoredIndex() + 1;
    auto result = mBackend.storeSession(index, jsonDoc.as<std::string>());

    return result;
}

void SessionDatabase::deleteSession(std::size_t index)
{
    mBackend.deleteSession(index);
}

} // namespace LaptimerCore::Session

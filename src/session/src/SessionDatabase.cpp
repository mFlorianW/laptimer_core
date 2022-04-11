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
    return mIndicies.size();
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
    auto result = mBackend.storeSession(index, jsonDoc.as<std::string>());

    if (result)
    {
        mIndicies = mBackend.getIndexList();
    }

    return result;
}

void SessionDatabase::deleteSession(std::size_t index)
{
    auto result = mBackend.deleteSession(index);
    if (result)
    {
        mIndicies = mBackend.getIndexList();
    }
}

} // namespace LaptimerCore::Session

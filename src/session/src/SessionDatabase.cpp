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
    if (!Common::JsonSerializer::serializeSessionData(session, jsonRootObject))
    {
        return false;
    }

    // This is the case when the active session is stored.
    if (!mBackend.getIndexList().empty())
    {
        for (std::size_t index = 0; index < mBackend.getNumberOfStoredSessions(); ++index)
        {
            const auto storedSession =
                Common::JsonDeserializer::deserializeSessionData(mBackend.loadSessionByIndex(index));

            if (storedSession && (storedSession->getSessionDate() == session.getSessionDate()) &&
                (storedSession->getSessionTime() == session.getSessionTime()) &&
                (storedSession->getTrack() == session.getTrack()))
            {
                return mBackend.storeSession(index, jsonDoc.as<std::string>());
            }
        }
    }

    // This is the case when a new session is started.
    std::size_t storageIndex = (mBackend.getNumberOfStoredSessions() == 0) ? 0 : mBackend.getLastStoredIndex() + 1;
    return mBackend.storeSession(storageIndex, jsonDoc.as<std::string>());
}

void SessionDatabase::deleteSession(std::size_t index)
{
    const auto deleted = mBackend.deleteSession(index);
    if (deleted)
    {
        sessionDeleted.emit(index);
    }
}

} // namespace LaptimerCore::Session

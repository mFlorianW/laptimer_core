#include "SessionDatabase.hpp"
#include "AsyncResultDb.hpp"
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

std::shared_ptr<System::AsyncResult> SessionDatabase::storeSession(const Common::SessionData &session)
{
    ArduinoJson::StaticJsonDocument<8192> jsonDoc;
    auto result = std::make_shared<AsyncResultDb>();
    auto jsonRootObject = jsonDoc.to<ArduinoJson::JsonObject>();
    if (!Common::JsonSerializer::serializeSessionData(session, jsonRootObject))
    {
        result->setDbResult(System::Result::Error);
        return result;
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
                const auto updated = mBackend.storeSession(index, jsonDoc.as<std::string>());
                if (updated)
                {
                    sessionUpdated.emit(index);
                }

                const auto updateResult = updated ? System::Result::Ok : System::Result::Error;
                result->setDbResult(updateResult);
                return result;
            }
        }
    }

    // This is the case when a new session is started.
    std::size_t storageIndex = (mBackend.getNumberOfStoredSessions() == 0) ? 0 : mBackend.getLastStoredIndex() + 1;
    const auto stored = mBackend.storeSession(storageIndex, jsonDoc.as<std::string>());
    if (stored)
    {
        sessionAdded.emit(storageIndex);
    }
    const auto storeResult = stored ? System::Result::Ok : System::Result::Error;
    result->setDbResult(storeResult);
    return result;
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

#ifndef SESSIONDATABASE_HPP
#define SESSIONDATABASE_HPP

#include "ISessionDatabase.hpp"
#include "ISessionDatabaseBackend.hpp"

namespace LaptimerCore::Session
{

class SessionDatabase : public ISessionDatabase
{
public:
    /**
     * Constructs a SessionDatabase
     * @param backend The backend that handle all storage operations. Must live as long as the SessionDatabase.
     */
    SessionDatabase(ISessionDatabaseBackend &backend);

    /**
     * Default Destructor
     */
    virtual ~SessionDatabase();

    std::size_t getSessionCount() override;
    Common::SessionData getLastSession() const noexcept override;
    std::optional<Common::SessionData> getSessionByIndex(std::size_t index) const noexcept override;
    std::optional<Common::SessionData> getSessionByDate(const Common::Timestamp &sessionData) const noexcept override;
    bool storeSession(const Common::SessionData &session) override;

private:
    ISessionDatabaseBackend &mBackend;
};

} // namespace LaptimerCore::Session

#endif // SESSIONDATABASE_HPP

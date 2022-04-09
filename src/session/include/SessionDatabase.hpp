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

    /**
     * Gives the number of stored session.
     * @return The number of the stored session.
     */
    std::size_t getSessionCount() override;

    /**
     * Gives the session by the past index.
     * @param index The index of the session.
     * @return The session or a std::nullopt if no session is present.
     */
    std::optional<Common::SessionData> getSessionByIndex(std::size_t index) const noexcept override;

    /**
     * Stores the passed session.
     * @param session The session that shall be stored.
     * @return True Session succesful stored
     * @return False Failed to store the session.
     */
    bool storeSession(const Common::SessionData &session) override;

private:
    ISessionDatabaseBackend &mBackend;
};

} // namespace LaptimerCore::Session

#endif // SESSIONDATABASE_HPP

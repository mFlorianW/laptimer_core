#ifndef ISESSIONDATABASE_HPP
#define ISESSIONDATABASE_HPP

#include "SessionData.hpp"

namespace LaptimerCore::Session
{

class ISessionDatabase
{
public:
    /**
     * Default destrutor
     */
    virtual ~ISessionDatabase() = default;

    /**
     * Gives the number of stored sessions
     * @return The number of stored sessions.
     */
    virtual std::size_t getSessionCount() = 0;

    /**
     * Gives you the last used session. If no session is present a
     * default constructed session will be returned.
     * @return The last used session.
     */
    virtual Common::SessionData getLastSession() const noexcept;

    /**
     * Gives the session by the index. If index doesn't exists a nullopt is returned.
     * @param index The index of the request session.
     * @return The session by the given index or a nullopt.
     */
    virtual std::optional<Common::SessionData> getSessionByIndex(std::size_t index) const noexcept;

    /**
     * Gives the a session for the given timestamp.
     * @return Session if present otherwise nullopt;
     */
    virtual std::optional<Common::SessionData> getSessionByDate(
        const Common::Timestamp &sessionData) const noexcept = 0;

    /**
     * Stores the given session.
     * @param session The session that shall bestored.
     * @return True session successful stored otherwise false.
     */
    virtual bool storeSession(const Common::SessionData session) = 0;

protected:
    ISessionDatabase() = default;
};

} // namespace LaptimerCore::Session

#endif // ISESSION_HPP

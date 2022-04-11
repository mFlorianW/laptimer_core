#ifndef ISESSIONDATABASE_HPP
#define ISESSIONDATABASE_HPP

#include "SessionData.hpp"

namespace LaptimerCore::Session
{
/**
 * The SessionDatabase provides an index based access to the stored session data.
 */
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
     * Gives the session by the index. If index doesn't exists a nullopt is returned.
     * @param index The index of the request session.
     * @return The session by the given index or a nullopt.
     */
    virtual std::optional<Common::SessionData> getSessionByIndex(std::size_t index) const noexcept = 0;

    /**
     * Stores the given session.
     * @param session The session that shall bestored.
     * @return True session successful stored otherwise false.
     */
    virtual bool storeSession(const Common::SessionData &session) = 0;

    /**
     * Deletes the session under the given index.
     * If the index is not present nothing happens.
     * @param index The index which shall deleted.
     */
    virtual void deleteSession(std::size_t index) = 0;

protected:
    ISessionDatabase() = default;
};

} // namespace LaptimerCore::Session

#endif // ISESSION_HPP

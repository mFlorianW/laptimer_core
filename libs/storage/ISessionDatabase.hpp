#ifndef ISESSIONDATABASE_HPP
#define ISESSIONDATABASE_HPP

#include "AsyncResult.hpp"
#include "SessionData.hpp"
#include <kdbindings/signal.h>
#include <memory>

namespace LaptimerCore::Storage
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
     * Deleted copy constructor
     */
    ISessionDatabase(const ISessionDatabase &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    ISessionDatabase &operator=(const ISessionDatabase &other) = delete;

    /**
     * Deleted move constructor
     */
    ISessionDatabase(ISessionDatabase &&ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    ISessionDatabase &operator=(ISessionDatabase &&other) = delete;

    /**
     * Gives the number of stored sessions and defines the width of indexs. The session
     * are accessable from 0...[SessionCount].
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
    virtual std::shared_ptr<System::AsyncResult> storeSession(const Common::SessionData &session) = 0;

    /**
     * Deletes the session under the given index.
     * If the index is not present nothing happens.
     * @param index The index which shall deleted.
     */
    virtual void deleteSession(std::size_t index) = 0;

    /**
     * This signal shall be emitted by a session database, when a new session is stored.
     * @param index The index that got added to the database.
     */
    KDBindings::Signal<std::size_t> sessionAdded;

    /**
     * This signal shall be emitted by a session database, when a session is updated.
     * @param index The index of the session that got updated.
     */
    KDBindings::Signal<std::size_t> sessionUpdated;

    /**
     * This signal shall be emitted by a session database when a session is deleted.
     * @param index The index of the session that got deleted.
     */
    KDBindings::Signal<std::size_t> sessionDeleted;

protected:
    ISessionDatabase() = default;
};

} // namespace LaptimerCore::Storage

#endif // ISESSION_HPP

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef SESSIONDATABASE_HPP
#define SESSIONDATABASE_HPP

#include "ISessionDatabase.hpp"
#include "ISessionDatabaseBackend.hpp"

namespace Rapid::Storage
{

class SessionDatabase : public ISessionDatabase
{
public:
    /**
     * Constructs a SessionDatabase
     * @param backend The backend that handle all storage operations. Must live as long as the SessionDatabase.
     */
    SessionDatabase(ISessionDatabaseBackend& backend);

    /**
     * Default Destructor
     */
    ~SessionDatabase() override;

    /**
     * Disabled copy operator
     */
    SessionDatabase(SessionDatabase const&) = delete;

    /**
     * Disabled copy operator
     */
    SessionDatabase& operator=(SessionDatabase const&) = delete;

    /**
     * Disabled move operator
     */
    SessionDatabase(SessionDatabase&&) noexcept = delete;

    /**
     * Disabled move operator
     */
    SessionDatabase& operator=(SessionDatabase&&) noexcept = delete;

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
     * @copydoc ISessionDatabase::storeSession(const Common::SessionData &session)
     */
    std::shared_ptr<System::AsyncResult> storeSession(Common::SessionData const& session) override;

    /**
     * @copydoc ISessionDatabase::deleteSession(std::size_t index)
     */
    void deleteSession(std::size_t index) override;

private:
    ISessionDatabaseBackend& mBackend;
};

} // namespace Rapid::Storage

#endif // SESSIONDATABASE_HPP

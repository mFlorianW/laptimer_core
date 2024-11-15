// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef LAPTIMERCORE_FILESYSTEMSESSIONDATABASEBACKEND_HPP
#define LAPTIMERCORE_FILESYSTEMSESSIONDATABASEBACKEND_HPP

#include "ISessionDatabaseBackend.hpp"

namespace Rapid::Storage
{

/**
 * SessionDatabase backend that uses a file system to store the session data.
 * The doesn't database backend doesn't create the folder that it's uses for
 * storing the data. It's in the responsibility of the user that the folder
 * exists.
 */
class FileSystemSessionDatabaseBackend final : public ISessionDatabaseBackend
{
public:
    FileSystemSessionDatabaseBackend(std::string const& databaseFolder);
    ~FileSystemSessionDatabaseBackend() override = default;

    /**
     * Deleted copy constructor
     */
    FileSystemSessionDatabaseBackend(FileSystemSessionDatabaseBackend const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    FileSystemSessionDatabaseBackend& operator=(FileSystemSessionDatabaseBackend const& other) = delete;

    /**
     * Deleted move constructor
     */
    FileSystemSessionDatabaseBackend(FileSystemSessionDatabaseBackend&& ohter) = delete;

    /**
     * Deleted move assignemnt operator
     */
    FileSystemSessionDatabaseBackend& operator=(FileSystemSessionDatabaseBackend&& other) = delete;

    /**
     * @copydoc ISessionDatabaseBackend::getLastStoredIndex()
     */
    size_t getLastStoredIndex() const noexcept override;

    /**
     * @copydoc ISessionDatabaseBackend::getIndexList()
     */
    std::vector<std::size_t> getIndexList() const noexcept override;

    /**
     * @copydoc ISessionDatabaseBackend::
     */
    size_t getNumberOfStoredSessions() const noexcept override;

    /**
     * @copydoc ISessionDatabaseBackend::storeSession
     */
    bool storeSession(std::size_t index, std::string const& sessionData) override;

    /**
     * @copydoc ISessionDatabaseBackend::loadSessionByIndex
     */
    std::string loadSessionByIndex(std::size_t index) override;

    /**
     * @copydoc ISessionDatabaseBackend::deleteSession
     */
    bool deleteSession(std::size_t index) override;

private:
    std::string mDbDir;
    std::size_t mLastStoredIndex{0};
};

} // namespace Rapid::Storage

#endif // LAPTIMERCORE_FILESYSTEMSESSIONDATABASEBACKEND_HPP

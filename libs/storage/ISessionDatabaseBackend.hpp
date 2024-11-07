// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef ISESIONDATABASEBACKEND_HPP
#define ISESIONDATABASEBACKEND_HPP

#include <ArduinoJson.hpp>
#include <vector>

namespace Rapid::Storage
{

class ISessionDatabaseBackend
{
public:
    virtual ~ISessionDatabaseBackend() = default;

    /**
     * Disabled copy operator
     */
    ISessionDatabaseBackend(ISessionDatabaseBackend const&) = delete;

    /**
     * Disabled copy operator
     */
    ISessionDatabaseBackend& operator=(ISessionDatabaseBackend const&) = delete;

    /**
     * Disabled move operator
     */
    ISessionDatabaseBackend(ISessionDatabaseBackend&&) noexcept = delete;

    /**
     * Disabled move operator
     */
    ISessionDatabaseBackend& operator=(ISessionDatabaseBackend&&) noexcept = delete;

    virtual std::size_t getLastStoredIndex() const noexcept = 0;

    virtual std::vector<std::size_t> getIndexList() const noexcept = 0;

    virtual std::size_t getNumberOfStoredSessions() const noexcept = 0;

    virtual bool storeSession(std::size_t index, std::string const& sessionData) = 0;

    virtual std::string loadSessionByIndex(std::size_t index) = 0;

    virtual bool deleteSession(std::size_t index) = 0;

protected:
    ISessionDatabaseBackend() = default;
};

} // namespace Rapid::Storage

#endif // ISESIONDATABASEBACKEND_HPP

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QSettings>
#include <QVariant>

namespace LaptimerCore::LappyShell
{
/**
 * Forard declaration for settings backend
 */
class ISettingsBackend;

/**
 * Write only interfacce for the global settings of the Shell
 */
class GlobalSettingsWriter
{
public:
    /**
     * Constructs a @ref LaptimerCore::LappyShell::Settings instance
     * @param settingsBackend The settings that execute the concret store operations
     *                        The Settings doesn't take the ownership of the pointer so the caller must
     *                        guarantee that the object is valid as long the Settings class exists.
     */
    GlobalSettingsWriter(ISettingsBackend* settingsBackend);

    /**
     * Default destructor
     */
    ~GlobalSettingsWriter();

    /**
     * Deleted copy operator
     */
    GlobalSettingsWriter& operator=(GlobalSettingsWriter const&) = delete;

    /**
     * Deleted copy constructor
     */
    GlobalSettingsWriter(GlobalSettingsWriter const&) = delete;

    /**
     * Deleted move operator
     */
    GlobalSettingsWriter& operator=(GlobalSettingsWriter&&) noexcept = delete;

    /**
     * Deleted move constructor
     */
    GlobalSettingsWriter(GlobalSettingsWriter const&&) noexcept = delete;

    /**
     * Stores the database file path
     * @param dbFilePath The new database file path that shall be stored.
     * @return True successful stored
     *         false Failed to store
     */
    [[nodiscard]] bool storeDatabaseFilePath(QString const& dbFilePath) noexcept;

private:
    ISettingsBackend* mSettingsBackend;
};

class ISettingsBackend
{
public:
    /**
     * Default destructor
     */
    ~ISettingsBackend() = default;

    /**
     * Deleted copy constructor
     */
    ISettingsBackend(ISettingsBackend const&) = delete;

    /**
     * Deleted copy operator
     */
    ISettingsBackend& operator=(ISettingsBackend const&) = delete;

    /**
     * Deleted copy constructor
     */
    ISettingsBackend(ISettingsBackend&&) noexcept = delete;

    /**
     * Deleted move operator
     */
    ISettingsBackend& operator=(ISettingsBackend&&) noexcept = delete;

    /**
     * Stores a value under the given key.
     * @param key The key under which the value shall be stored to load it later.
     * @param value The value that shall be stored.
     * @return true Successful stored.
     *         false Failed to store.
     */
    [[nodiscard]] virtual bool storeValue(QString const& key, QVariant const& value) noexcept = 0;

protected:
    ISettingsBackend() = default;
};

/**
 * QSettings based implementation of the @ref ISettingsBackend
 */
class QSettingsBackend : public ISettingsBackend
{
public:
    /**
     * Creates an instance of the QSettings backend
     */
    QSettingsBackend();

    /**
     * Default empty destructor
     */
    ~QSettingsBackend() = default;

    /**
     * Deleted copy constructor
     */
    QSettingsBackend(QSettingsBackend const&) = delete;

    /**
     * Deleted copy operator
     */
    QSettingsBackend& operator=(QSettingsBackend const&) = delete;

    /**
     * Deleted copy constructor
     */
    QSettingsBackend(QSettingsBackend&&) noexcept = delete;

    /**
     * Deleted move operator
     */
    QSettingsBackend& operator=(QSettingsBackend&&) noexcept = delete;

    /**
     * @copydoc ISettingsBackend::storeValue
     */
    bool storeValue(QString const& key, QVariant const& value) noexcept override;

private:
    QSettings mSettings;
};

} // namespace LaptimerCore::LappyShell

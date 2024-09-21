// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <GlobalSettingsBackend.hpp>
#include <QSettings>
#include <QVariant>

namespace LaptimerCore::LappyShell
{

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
    GlobalSettingsWriter(Common::GlobalSettingsBackend* settingsBackend);

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
    Common::GlobalSettingsBackend* mSettingsBackend;
};

} // namespace LaptimerCore::LappyShell

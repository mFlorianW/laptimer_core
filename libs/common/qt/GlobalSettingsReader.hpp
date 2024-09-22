// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <GlobalSettingsBackend.hpp>
#include <QString>

namespace LaptimerCore::Common
{
/**
 * Reads the global settings from the provided backend.
 */
class GlobalSettingsReader
{
public:
    /**
     * Creates an instance of the GlobalSettingsReader
     * @param settingsBackend The settings backend for the store and load operations
     */
    GlobalSettingsReader(GlobalSettingsBackend* settingsBackend);

    /**
     * Default destructor
     */
    ~GlobalSettingsReader();

    /**
     * Deleted copy constructor
     */
    GlobalSettingsReader(GlobalSettingsReader const&);

    /**
     * Deleted copy operator
     */
    GlobalSettingsReader& operator=(GlobalSettingsReader const&);

    /**
     * Deleted move constructor
     */
    GlobalSettingsReader(GlobalSettingsReader const&&) noexcept;

    /**
     * Deleted move operator
     */
    GlobalSettingsReader& operator=(GlobalSettingsReader&&) noexcept;

    /**
     * Gives the stored database file path.
     * If no database file is stored an empty string is returned.
     * @return Success: The stored database file path.
     *         Error: An emtpy string when not setting is found.
     */
    QString getDbFilePath() const noexcept;

private:
    GlobalSettingsBackend* mSettingsBackend;
};

} // namespace LaptimerCore::Common

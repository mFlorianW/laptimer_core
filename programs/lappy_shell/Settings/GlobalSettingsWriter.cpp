// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsWriter.hpp"
#include <GlobalSettingsKeys.hpp>

namespace Rapid::LappyShell::Settings
{

GlobalSettingsWriter::GlobalSettingsWriter(Common::GlobalSettingsBackend* settingsBackend)
    : mSettingsBackend{settingsBackend}
{
}

GlobalSettingsWriter::~GlobalSettingsWriter() = default;

bool GlobalSettingsWriter::storeDatabaseFilePath(QString const& dbFilePath) noexcept
{
    return mSettingsBackend->storeValue(Common::Private::DbFilePathKey, dbFilePath);
}

bool GlobalSettingsWriter::storeDeviceSettings(QList<Common::DeviceSettings> const& deviceSettings) noexcept
{
    if (deviceSettings.isEmpty()) {
        return true;
    }
    if (not mSettingsBackend->storeValue(Common::Private::DeviceSettingsSize, deviceSettings.size())) {
        return false;
    }
    for (qsizetype i = 0; i < deviceSettings.size(); ++i) {
        if (not mSettingsBackend->storeValue(Common::Private::DeviceSettingsName.toString().arg(i),
                                             deviceSettings[i].name) or
            not mSettingsBackend->storeValue(Common::Private::DeviceSettingsIp.toString().arg(i),
                                             deviceSettings[i].ip.toString()) or
            not mSettingsBackend->storeValue(Common::Private::DeviceSettingsPort.toString().arg(i),
                                             deviceSettings[i].port) or
            not mSettingsBackend->storeValue(Common::Private::DeviceSettingsDef.toString().arg(i),
                                             deviceSettings[i].defaultDevice)) {
            return false;
        }
    }
    return true;
}

} // namespace Rapid::LappyShell::Settings

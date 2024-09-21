// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsWriter.hpp"

namespace LaptimerCore::LappyShell
{

GlobalSettingsWriter::GlobalSettingsWriter(ISettingsBackend* settingsBackend)
    : mSettingsBackend{settingsBackend}
{
}

GlobalSettingsWriter::~GlobalSettingsWriter() = default;

bool GlobalSettingsWriter::storeDatabaseFilePath(QString const& dbFilePath) noexcept
{
    return mSettingsBackend->storeValue("dbFilePath", dbFilePath);
}

QSettingsBackend::QSettingsBackend()
    : mSettings{QStringLiteral("lappy"), QStringLiteral("lappy")}
{
}

bool QSettingsBackend::storeValue(QString const& key, QVariant const& value) noexcept
{
    mSettings.setValue(key, value);
    return true;
}

} // namespace LaptimerCore::LappyShell

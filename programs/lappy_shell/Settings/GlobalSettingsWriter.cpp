// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsWriter.hpp"

namespace LaptimerCore::LappyShell
{

GlobalSettingsWriter::GlobalSettingsWriter(Common::GlobalSettingsBackend* settingsBackend)
    : mSettingsBackend{settingsBackend}
{
}

GlobalSettingsWriter::~GlobalSettingsWriter() = default;

bool GlobalSettingsWriter::storeDatabaseFilePath(QString const& dbFilePath) noexcept
{
    return mSettingsBackend->storeValue("dbFilePath", dbFilePath);
}

} // namespace LaptimerCore::LappyShell

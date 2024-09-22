// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsReader.hpp"
#include "GlobalSettingsKeys.hpp"

namespace LaptimerCore::Common
{

GlobalSettingsReader::GlobalSettingsReader(GlobalSettingsBackend* settingsBackend)
    : mSettingsBackend{settingsBackend}
{
}

GlobalSettingsReader::~GlobalSettingsReader() = default;

QString GlobalSettingsReader::getDbFilePath() const noexcept
{
    return mSettingsBackend->getValue(Private::DbFilePathKey).toString();
}

} // namespace LaptimerCore::Common

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsBackend.hpp"

namespace LaptimerCore::Common
{

QSettingsBackend::QSettingsBackend()
    : mSettings{QStringLiteral("lappy"), QStringLiteral("lappy")}
{
}

bool QSettingsBackend::storeValue(QString const& key, QVariant const& value) noexcept
{
    mSettings.setValue(key, value);
    return true;
}

} // namespace LaptimerCore::Common

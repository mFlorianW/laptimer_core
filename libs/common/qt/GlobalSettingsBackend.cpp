// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsBackend.hpp"

namespace Rapid::Common
{

QSettingsBackend::QSettingsBackend()
    : mSettings{QStringLiteral("rapid"), QStringLiteral("rapid")}
{
}

bool QSettingsBackend::storeValue(QAnyStringView const& key, QVariant const& value) noexcept
{
    mSettings.setValue(key, value);
    return true;
}

QVariant QSettingsBackend::getValue(QAnyStringView const& key) const noexcept
{
    return mSettings.value(key);
}

} // namespace Rapid::Common

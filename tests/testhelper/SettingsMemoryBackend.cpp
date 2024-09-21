// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SettingsMemoryBackend.hpp"

namespace LaptimerCore::TestHelper
{
bool SettingsMemoryBackend::storeValue(QString const& key, QVariant const& value) noexcept
{
    mSingleValues.insert(key, value);
    return true;
}

QVariant SettingsMemoryBackend::getValue(QString const& key) const noexcept
{
    return mSingleValues[key];
}

} // namespace LaptimerCore::TestHelper

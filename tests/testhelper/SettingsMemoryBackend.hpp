// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <GlobalSettingsBackend.hpp>

namespace LaptimerCore::TestHelper
{

class SettingsMemoryBackend : public Common::GlobalSettingsBackend
{
public:
    [[nodiscard]] bool storeValue(QString const& key, QVariant const& value) noexcept override;

    [[nodiscard]] QVariant getValue(QString const& key) const noexcept override;

private:
    QVariantHash mSingleValues;
};

} // namespace LaptimerCore::TestHelper

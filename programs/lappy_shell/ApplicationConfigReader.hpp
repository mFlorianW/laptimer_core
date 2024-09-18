// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "ApplicationConfig.hpp"
#include <optional>

namespace LaptimerCore::LappyShell
{

class ApplicationConfigReader
{
public:
    std::optional<ApplicationConfig> readConfig(QString const &configPath) const noexcept;
};

} // namespace LaptimerCore::LappyShell

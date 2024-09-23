// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DevicePage.hpp"
#include "ui_DevicePage.h"

namespace LaptimerCore::LappyShell::Settings
{

DevicePage::DevicePage()
    : mDevicePage{std::make_unique<Ui::DevicePage>()}
{
    mDevicePage->setupUi(this);
}

DevicePage::~DevicePage() = default;

} // namespace LaptimerCore::LappyShell::Settings

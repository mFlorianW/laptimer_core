// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsWindow.hpp"
#include "ui_GlobalSettingsWindow.h"

namespace LaptimerCore::LappyShell::Settings
{

GlobalSettingsWindow::GlobalSettingsWindow()
    : mGlobalSettingsWindow{std::make_unique<Ui::GlobalSettingsWindow>()}
{
    mGlobalSettingsWindow->setupUi(this);
}

GlobalSettingsWindow::~GlobalSettingsWindow() = default;

}; // namespace LaptimerCore::LappyShell::Settings

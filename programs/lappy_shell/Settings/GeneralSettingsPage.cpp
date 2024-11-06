// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GeneralSettingsPage.hpp"
#include "ui_GeneralSettingsPage.h"

namespace Rapid::LappyShell::Settings
{

GeneralSettingsPage::GeneralSettingsPage()
    : mGeneralSettings{std::make_unique<Ui::GeneralSettingsPage>()}
{
    mGeneralSettings->setupUi(this);
}

GeneralSettingsPage::~GeneralSettingsPage() = default;

} // namespace Rapid::LappyShell::Settings

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "GlobalSettingsWindow.hpp"
#include "ui_GlobalSettingsWindow.h"
#include <QIcon>

namespace LaptimerCore::LappyShell::Settings
{

GlobalSettingsWindow::GlobalSettingsWindow()
    : mGlobalSettingsWindow{std::make_unique<Ui::GlobalSettingsWindow>()}
{
    mGlobalSettingsWindow->setupUi(this);
    mGlobalSettingsWindow->listWidget->setFixedWidth(150);

    auto* settingsGeneral = mGlobalSettingsWindow->listWidget->item(0);
    settingsGeneral->setIcon(QIcon{QStringLiteral(":/qt/qml/Lappy/Settings/icons/settings.svg")});
    auto* deviceSettings = mGlobalSettingsWindow->listWidget->item(1);
    deviceSettings->setIcon(QIcon{QStringLiteral(":/qt/qml/Lappy/Settings/icons/device.svg")});

    auto* settingsListWidget = mGlobalSettingsWindow->listWidget;
    connect(settingsListWidget, &QListWidget::currentRowChanged, this, [this](int currentRow) {
        auto* item = mGlobalSettingsWindow->listWidget->item(currentRow);
        mGlobalSettingsWindow->ContentGroupBox->setTitle(item->text());
    });
    settingsListWidget->setCurrentRow(0);
}

GlobalSettingsWindow::~GlobalSettingsWindow() = default;

}; // namespace LaptimerCore::LappyShell::Settings

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
    , mSettingsPages{std::make_unique<QStackedLayout>()}
    , mGeneralSettingsPage{std::make_unique<GeneralSettingsPage>()}
    , mDevicePage{std::make_unique<DevicePage>(&mSettingsWriter)}
{
    mGlobalSettingsWindow->setupUi(this);
    mGlobalSettingsWindow->listWidget->setFixedWidth(150);
    mGlobalSettingsWindow->ContentGroupBox->setLayout(mSettingsPages.get());
    mSettingsPages->addWidget(mGeneralSettingsPage.get());
    mSettingsPages->addWidget(mDevicePage.get());

    auto* settingsGeneral = mGlobalSettingsWindow->listWidget->item(0);
    settingsGeneral->setIcon(QIcon{QStringLiteral(":/qt/qml/Lappy/Settings/icons/settings.svg")});
    auto* deviceSettings = mGlobalSettingsWindow->listWidget->item(1);
    deviceSettings->setIcon(QIcon{QStringLiteral(":/qt/qml/Lappy/Settings/icons/device.svg")});

    auto* settingsListWidget = mGlobalSettingsWindow->listWidget;
    connect(settingsListWidget, &QListWidget::currentRowChanged, this, [this](int currentRow) {
        auto* contentGrpBox = mGlobalSettingsWindow->ContentGroupBox;
        if (currentRow == 0) {
            contentGrpBox->setTitle(tr("General Settings"));
            mSettingsPages->setCurrentIndex(0);
        } else if (currentRow == 1) {
            contentGrpBox->setTitle(tr("Device Settings"));
            mSettingsPages->setCurrentIndex(1);
        }
    });
    settingsListWidget->setCurrentRow(0);
}

GlobalSettingsWindow::~GlobalSettingsWindow() = default;

}; // namespace LaptimerCore::LappyShell::Settings

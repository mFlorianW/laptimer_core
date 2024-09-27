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
    // Setup device page
    mDevicePage->setupUi(this);

    // Setup header view
    mHeaderView.setModel(&mDeviceModel);
    mHeaderView.setStretchLastSection(true);

    // Setup device model
    mDevicePage->deviceTable->setHorizontalHeader(&mHeaderView);
    mDevicePage->deviceTable->setModel(&mDeviceModel);

    // Setup Add Handler
    connect(mDevicePage->addButton, &QPushButton::clicked, this, [this]() {
        mDeviceModel.insertRows(mDeviceModel.rowCount({}));
    });

    connect(mDevicePage->removeButton, &QPushButton::clicked, this, [this]() {
        auto const selectionModel = mDevicePage->deviceTable->selectionModel();
        if (selectionModel->hasSelection()) {
            auto const selectedIndex = mDevicePage->deviceTable->selectionModel()->selectedIndexes().first();
            if (selectedIndex.isValid()) {
                mDeviceModel.removeRows(selectedIndex.row());
            }
        }
    });
}

DevicePage::~DevicePage() = default;

} // namespace LaptimerCore::LappyShell::Settings

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QWidget>
#include <memory>

namespace Ui
{
class DevicePage;
}

namespace LaptimerCore::LappyShell::Settings
{

/**
 * Defines the content for devices page in the global shell settings.
 */
class DevicePage : public QWidget
{
    Q_OBJECT
public:
    /**
     * Creates an Instance of the device settings pagage.
     */
    DevicePage();

    /**
     * default destructor
     */
    ~DevicePage() override;

    /*
     * Disabled copy and move semantics
     */
    Q_DISABLE_COPY_MOVE(DevicePage)

private:
    std::unique_ptr<Ui::DevicePage> mDevicePage;
};

} // namespace LaptimerCore::LappyShell::Settings

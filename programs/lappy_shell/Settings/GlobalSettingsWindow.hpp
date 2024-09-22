// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QDialog>
#include <QtGlobal>
#include <memory>

namespace Ui
{
class GlobalSettingsWindow;
}

namespace LaptimerCore::LappyShell::Settings
{

class GlobalSettingsWindow : public QDialog
{
    Q_OBJECT
public:
    GlobalSettingsWindow();
    ~GlobalSettingsWindow() override;

    Q_DISABLE_COPY_MOVE(GlobalSettingsWindow);

private:
    std::unique_ptr<Ui::GlobalSettingsWindow> mGlobalSettingsWindow;
};

} // namespace LaptimerCore::LappyShell::Settings

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <GlobalSettingsWindow.hpp>
#include <GlobalSettingsWriter.hpp>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
} // namespace Ui

namespace LaptimerCore::LappyShell
{

class LappyShell : public QMainWindow
{
    Q_OBJECT
public:
    LappyShell();
    ~LappyShell() override;

    Q_DISABLE_COPY_MOVE(LappyShell)

private:
    void setupDatabase() noexcept;
    std::unique_ptr<Ui::MainWindow> mMainWindow;
    Common::QSettingsBackend mSettingsBackend;
    Settings::GlobalSettingsWriter mSettings;
    std::unique_ptr<Settings::GlobalSettingsWindow> mGlobalSettingsWindow;
};

} // namespace LaptimerCore::LappyShell

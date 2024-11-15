// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <ApplicationOverviewWidget.hpp>
#include <GlobalSettingsWindow.hpp>
#include <GlobalSettingsWriter.hpp>
#include <QMainWindow>

namespace Ui
{
class MainWindow;
} // namespace Ui

namespace Rapid::RapidShell
{

class RapidShell : public QMainWindow
{
    Q_OBJECT
public:
    RapidShell();
    ~RapidShell() override;

    Q_DISABLE_COPY_MOVE(RapidShell)

private:
    void setupDatabase() noexcept;
    std::unique_ptr<Ui::MainWindow> mMainWindow;
    Common::QSettingsBackend mSettingsBackend;
    Settings::GlobalSettingsWriter mSettings;
    std::unique_ptr<ProcessManager> mProcessManager;
    std::unique_ptr<Settings::GlobalSettingsWindow> mGlobalSettingsWindow;
    std::unique_ptr<ApplicationOverviewWidget> mApplicationOverviewWidget;
};

} // namespace Rapid::RapidShell

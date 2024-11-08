// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "RapidShell.hpp"
#include "DatabaseFile.hpp"
#include "LoggingCategories.hpp"
#include "ui_MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QQmlContext>
#include <QStandardPaths>

namespace Rapid::RapidShell
{

RapidShell::RapidShell()
    : mMainWindow{std::make_unique<Ui::MainWindow>()}
    , mSettings{&mSettingsBackend}
    , mProcessManager{std::make_unique<ProcessManager>()}
    , mGlobalSettingsWindow{std::make_unique<Settings::GlobalSettingsWindow>()}
    , mApplicationOverviewWidget{std::make_unique<ApplicationOverviewWidget>(mProcessManager.get())}
{
    setupDatabase();
    mMainWindow->setupUi(this);

    // Set Application Overview
    mMainWindow->centralwidget->layout()->addWidget(mApplicationOverviewWidget.get());

    connect(mMainWindow->actionQuit, &QAction::triggered, this, []() {
        QApplication::exit();
    });

    connect(mMainWindow->actionPreferences, &QAction::triggered, this, [this]() {
        mGlobalSettingsWindow->show();
    });
}

RapidShell::~RapidShell() = default;

void RapidShell::setupDatabase() noexcept
{
    auto const dbLocation =
        QString{"%1/%2"}.arg(QStandardPaths::writableLocation(QStandardPaths::StandardLocation::GenericDataLocation),
                             QStringLiteral("rapid"));
    auto const dbFile = QString{"%1%2"}.arg(dbLocation, QStringLiteral("/rapid.db"));
    if (not QFile::exists(dbFile)) {
        qCInfo(rapid_shell) << "No database found! Copy empty default database to" << dbLocation;
        auto dbDir = QDir{};
        if (not dbDir.exists(dbLocation)) {
            qCInfo(rapid_shell) << "Database location doesn't exists." << dbLocation;
            if (not dbDir.mkdir(dbLocation)) {
                qCCritical(rapid_shell) << "Failed to create database location." << dbFile;
            } else {
                qCInfo(rapid_shell) << "Database location created't exists." << dbLocation;
            }
        } else {
            qCInfo(rapid_shell) << "Database location exists." << dbLocation;
        }

        if (not QFile::copy(DATABASE_FILE, dbFile)) {
            qCCritical(rapid_shell) << "Failed to copy empty database to:" << dbFile;
        } else {
            qCInfo(rapid_shell) << "Copied empty database to:" << dbFile;
        }
    }

    if (not mSettings.storeDatabaseFilePath(dbFile)) {
        qCCritical(rapid_shell) << "Failed to store database file parameter in global settings.";
    }
}

} // namespace Rapid::RapidShell

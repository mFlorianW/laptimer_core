// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LappyShell.hpp"
#include "DatabaseFile.hpp"
#include "LoggingCategories.hpp"
#include <QDir>
#include <QFile>
#include <QQmlContext>
#include <QQuickWindow>
#include <QStandardPaths>
#include <qdiriterator.h>

namespace LaptimerCore::LappyShell
{

LappyShell::LappyShell()
{
    setupDatabase();
    mEngine.load(QUrl{"qrc:/qt/qml/Lappy/Shell/qml/MainWindow.qml"});
}

void LappyShell::show() const noexcept
{
    auto* topLevel = mEngine.rootObjects().value(0);
    auto* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();
}

void LappyShell::setupDatabase() noexcept
{
    auto const dbLocation =
        QString{"%1/%2"}.arg(QStandardPaths::writableLocation(QStandardPaths::StandardLocation::GenericDataLocation),
                             QStringLiteral("lappy"));
    auto const dbFile = QString{"%1%2"}.arg(dbLocation, QStringLiteral("/lappy.db"));
    if (not QFile::exists(dbFile)) {
        qCInfo(lappy_shell) << "No database found! Copy empty default database to" << dbLocation;
        auto dbDir = QDir{};
        if (not dbDir.exists(dbLocation)) {
            qCInfo(lappy_shell) << "Database location doesn't exists." << dbLocation;
            if (not dbDir.mkdir(dbLocation)) {
                qCCritical(lappy_shell) << "Failed to create database location." << dbFile;
            } else {
                qCInfo(lappy_shell) << "Database location created't exists." << dbLocation;
            }
        } else {
            qCInfo(lappy_shell) << "Database location exists." << dbLocation;
        }

        if (not QFile::copy(DATABASE_FILE, dbFile)) {
            qCCritical(lappy_shell) << "Failed to copy empty database to:" << dbFile;
        } else {
            qCInfo(lappy_shell) << "Copied empty database to:" << dbFile;
        }
    }
}

} // namespace LaptimerCore::LappyShell

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SessionDownloader.hpp"
#include <GlobalSettingsReader.hpp>
#include <LoggingCategories.hpp>
#include <QDebug>
#include <QQmlContext>
#include <QQuickWindow>

namespace Rapid::SessionDl
{

SessionDownloader::SessionDownloader(QHostAddress const& address, quint16 port) noexcept
{
    auto settingsBackend = Common::QSettingsBackend{};
    auto const settings = Common::GlobalSettingsReader{&settingsBackend};
    auto const dbFilePath = settings.getDbFilePath();
    if (dbFilePath.isEmpty()) {
        qCCritical(sessiondl) << "No database found please! Start session download from LappyShell.";
    } else {
        qCInfo(sessiondl) << "Sessions will be stored in database:" << dbFilePath;
    }

    mDatabase = std::make_unique<Storage::SqliteSessionDatabase>(dbFilePath.toStdString());
    mMainWindowModel = std::make_unique<MainWindowModel>(mSessionDownloader, *mDatabase);

    auto qmlContext = mEngine.rootContext();
    qmlContext->setContextProperty("g_MainWindowModel", mMainWindowModel.get());
    mEngine.load(QUrl{"qrc:/qt/qml/Rapid/SessionDownloader/qml/MainWindow.qml"});

    mClient.setServerAddress(address.toString().toStdString());
    mClient.setServerPort(port);

    mMainWindowModel->setHostAddress(address);
    mMainWindowModel->setHostPort(port);
}

void SessionDownloader::show() const noexcept
{
    auto* topLevel = mEngine.rootObjects().value(0);
    auto* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();
}

} // namespace Rapid::SessionDl

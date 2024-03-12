// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LappySessionDownloader.hpp"
#include <QQmlContext>
#include <QQuickWindow>

namespace LaptimerCore::SessionDl
{

LappySessionDownloader::LappySessionDownloader(QHostAddress const& address, quint16 port) noexcept
{
    auto qmlContext = mEngine.rootContext();
    qmlContext->setContextProperty("g_MainWindowModel", &mMainWindowModel);
    mEngine.load(QUrl{"qrc:/qml/MainWindow.qml"});

    mClient.setServerAddress(address.toString().toStdString());
    mClient.setServerPort(port);

    mMainWindowModel.setHostAddress(address);
    mMainWindowModel.setHostPort(port);
}

void LappySessionDownloader::show() const noexcept
{
    auto* topLevel = mEngine.rootObjects().value(0);
    auto* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();
}

} // namespace LaptimerCore::SessionDl

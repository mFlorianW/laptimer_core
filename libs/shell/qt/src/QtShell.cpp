// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "QtShell.hpp"
#include "EventLoop.hpp"
#include "MainWindowViewModel.hpp"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>
#include <Timer.hpp>

namespace LaptimerCore::QtShell
{

struct QtShellPrivate
{
    QQmlApplicationEngine engine;
    MainWindowViewModel mMainWindowViewModel;
};

QtShell::QtShell()
    : d(std::make_unique<QtShellPrivate>())
{
    auto qmlContext = d->engine.rootContext();
    qmlContext->setContextProperty("g_MainWindowViewModel", &d->mMainWindowViewModel);

    d->engine.load(QUrl{"qrc:/qml/MainWindow.qml"});
}

QtShell::~QtShell() = default;

void QtShell::show()
{
    QObject* topLevel = d->engine.rootObjects().value(0);
    auto* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();
}

} // namespace LaptimerCore::QtShell

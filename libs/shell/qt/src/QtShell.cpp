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
    QTimer laptimerCoreTimer;
    System::EventLoop mEventLoop;
};

QtShell::QtShell()
    : d(std::make_unique<QtShellPrivate>())
{
    auto qmlContext = d->engine.rootContext();
    qmlContext->setContextProperty("g_MainWindowViewModel", &d->mMainWindowViewModel);

    d->engine.load(QUrl{"qrc:/qml/MainWindow.qml"});

    // TODO: move this in somehow in the mainloop
    d->laptimerCoreTimer.setInterval(5);
    QObject::connect(&d->laptimerCoreTimer, &QTimer::timeout, &d->laptimerCoreTimer, [=]() {
        d->mEventLoop.exec();
    });
    d->laptimerCoreTimer.start();
}

QtShell::~QtShell() = default;

void QtShell::show()
{
    QObject* topLevel = d->engine.rootObjects().value(0);
    auto* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();
}

} // namespace LaptimerCore::QtShell

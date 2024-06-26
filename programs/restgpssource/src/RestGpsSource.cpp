// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "RestGpsSource.hpp"
#include "EventLoop.hpp"
#include "MainWindowViewModel.hpp"
#include <QQmlContext>
#include <QQuickWindow>
#include <QTimer>
#include <Timer.hpp>

struct RestGpsSourcePrivate
{
    QQmlApplicationEngine mEngine;
    MainWindowViewModel mMainWindowViewModel;
    QTimer mLaptimerCoreTimer;
    LaptimerCore::System::EventLoop mEventLoop;
};

RestGpsSource::RestGpsSource()
    : d{std::make_unique<RestGpsSourcePrivate>()}
{
    auto qmlContext = d->mEngine.rootContext();
    qmlContext->setContextProperty("g_MainWindowViewModel", &d->mMainWindowViewModel);

    d->mEngine.load(QUrl{"qrc:/qml/MainWindow.qml"});

    // TODO: move this in somehow in the mainloop
    d->mLaptimerCoreTimer.setInterval(std::chrono::milliseconds(1));
    QObject::connect(&d->mLaptimerCoreTimer, &QTimer::timeout, &d->mLaptimerCoreTimer, [=]() {
        d->mEventLoop.processEvents();
    });
    d->mLaptimerCoreTimer.start();
}

RestGpsSource::~RestGpsSource() = default;

void RestGpsSource::show()
{
    auto* topLevel = d->mEngine.rootObjects().value(0);
    auto* window = qobject_cast<QQuickWindow*>(topLevel);
    window->show();
}

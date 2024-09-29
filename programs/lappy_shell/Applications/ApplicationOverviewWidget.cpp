// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ApplicationOverviewWidget.hpp"
#include <QQmlContext>
#include <QQmlEngine>

namespace LaptimerCore::LappyShell
{

ApplicationOverviewWidget::ApplicationOverviewWidget()
{
    // Load initial applications
    mAppModel.loadApplications();
    // Set context properties for the application
    rootContext()->setContextProperty("g_applicationModel", &mListModel);

    setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Load QML file
    setSource(QUrl{"qrc:/qt/qml/Lappy/Shell/Applications/qml/ApplicationOverview.qml"});

    // Load initial error and display them
    auto const errorList = errors();
    for (auto const& error : errorList) {
        onQmlError(QQuickWindow::SceneGraphError::ContextNotAvailable, error.toString());
    }
}

ApplicationOverviewWidget::~ApplicationOverviewWidget() = default;

void ApplicationOverviewWidget::onQmlError(QQuickWindow::SceneGraphError const& error, QString const& message)
{
    qCritical() << error << ":" << message;
}

} // namespace LaptimerCore::LappyShell

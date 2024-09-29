// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ApplicationOverviewWidget.hpp"
#include <QDirIterator>

namespace LaptimerCore::LappyShell
{

ApplicationOverviewWidget::ApplicationOverviewWidget()
    : QQuickWidget{QUrl{"qrc:/qt/qml/Lappy/Shell/Applications/qml/ApplicationOverview.qml"}}
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
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

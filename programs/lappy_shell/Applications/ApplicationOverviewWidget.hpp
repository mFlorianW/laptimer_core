// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "ApplicationListModel.hpp"
#include <QQuickWidget>

namespace LaptimerCore::LappyShell
{
class ApplicationOverviewWidget : public QQuickWidget
{
    Q_OBJECT
public:
    ApplicationOverviewWidget();
    ~ApplicationOverviewWidget() override;
    Q_DISABLE_COPY_MOVE(ApplicationOverviewWidget)
private Q_SLOTS:
    void onQmlError(QQuickWindow::SceneGraphError const& error, QString const& message);

private:
    ApplicationModel mAppModel = ApplicationModel{{"/home/florian/Coding/laptimer_core/build/debug-install/share/"}};
    ApplicationListModel mListModel = ApplicationListModel{mAppModel};
};
} // namespace LaptimerCore::LappyShell

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ApplicationOverviewWidget.hpp"
#include <LoggingCategories.hpp>
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
    rootContext()->setContextProperty("g_control", this);

    setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Load QML file
    setSource(QUrl{"qrc:/qt/qml/Lappy/Shell/Applications/qml/ApplicationOverview.qml"});

    // Load initial error and display them
    auto const errorList = errors();
    for (auto const& error : errorList) {
        onQmlError(QQuickWindow::SceneGraphError::ContextNotAvailable, error.toString());
    }
}

ApplicationOverviewWidget::~ApplicationOverviewWidget()
{
    for (auto const& [key, process] : mProcesses.asKeyValueRange()) {
        process->terminate();
        process->waitForFinished(1000);
        if (process->state() == QProcess::Running) {
            process->kill();
        }
    }
}

Q_INVOKABLE void ApplicationOverviewWidget::startApplication(QString const& exe) noexcept
{
    auto processRunning =
        std::find_if(mProcesses.cbegin(), mProcesses.cend(), [&exe](std::shared_ptr<QProcess> const& process) -> bool {
            if (process->program() == exe) {
                return true;
            }
            return false;
        }) != mProcesses.cend();

    if (processRunning) {
        return;
    }

    auto process = std::make_shared<QProcess>();
    mProcesses.insert(process.get(), process);
    process->setProgram(exe);
    process->start();
    connect(process.get(), &QProcess::finished, this, [this](int exitCode) {
        auto* process = qobject_cast<QProcess*>(sender());
        if (process == nullptr) {
            return;
        }
        qCInfo(lappy_shell_apps) << process->program() << "finished";
        if (mProcesses.contains(process)) {
            mProcesses.remove(process);
        }
    });

    connect(process.get(), &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        auto* process = qobject_cast<QProcess*>(sender());
        if (process == nullptr) {
            return;
        }
        qCInfo(lappy_shell_apps) << process->program() << "error occured.";
    });

    qCInfo(lappy_shell_apps) << "Process" << process->program() << "started";
}

void ApplicationOverviewWidget::onQmlError(QQuickWindow::SceneGraphError const& error, QString const& message)
{
    qCritical() << error << ":" << message;
}

} // namespace LaptimerCore::LappyShell

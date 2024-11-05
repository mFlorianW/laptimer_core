// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ProcessManager.hpp"
#include <QFileInfo>

namespace LaptimerCore::LappyShell
{

ProcessManager::ProcessManager() = default;

ProcessManager::~ProcessManager()
{
    for (auto const& [key, process] : mProcesses) {
        process->terminate();
        process->waitForFinished(std::chrono::seconds{1}.count());
    }
}

void ProcessManager::startProcess(QString const& processBinaryPath)
{
    auto pro = std::make_unique<QProcess>();
    connect(pro.get(), &QProcess::errorOccurred, this, [this](QProcess::ProcessError const& error) {
        auto process = qobject_cast<QProcess*>(sender());
        if (process != nullptr and error == QProcess::ProcessError::FailedToStart) {
            auto error = ProcessManager::Error::ProcessNotFound;
            Q_EMIT processError(process->program(), error);
        }
    });
    pro->setProgram(processBinaryPath);
    pro->start();
    mProcesses.insert({QFileInfo{processBinaryPath}.fileName(), std::move(pro)});
}

bool ProcessManager::isProcessRunning(QString const& process) const noexcept
{
    auto fileInfo = QFileInfo{process};
    auto processName = process;
    if (fileInfo.isAbsolute()) {
        processName = fileInfo.fileName();
    }
    return mProcesses.find(processName) != mProcesses.cend();
}

} // namespace LaptimerCore::LappyShell

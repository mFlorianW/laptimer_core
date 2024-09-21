// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "MainWindowModel.hpp"
#include <LibraryPath.hpp>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include <RestCall.hpp>
#include <SqliteSessionDatabase.hpp>

namespace LaptimerCore::SessionDl
{

class SessionDownloader final
{
public:
    SessionDownloader(QHostAddress const& dlAddress, quint16 port) noexcept;
    ~SessionDownloader() = default;

    Q_DISABLE_COPY_MOVE(SessionDownloader)

    void show() const noexcept;

private:
    QQmlApplicationEngine mEngine{};
    Rest::QRestClient mClient{};
    Workflow::RestSessionDownloader mSessionDownloader{mClient};
    Storage::SqliteSessionDatabase mDatabase{"/tmp/laptimer_core.db"};
    MainWindowModel mMainWindowModel{mSessionDownloader, mDatabase};
};

} // namespace LaptimerCore::SessionDl
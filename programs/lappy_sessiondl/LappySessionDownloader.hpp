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

class LappySessionDownloader final
{
public:
    LappySessionDownloader(QHostAddress const& dlAddress, quint16 port) noexcept;

    void show() const noexcept;

private:
    QQmlApplicationEngine mEngine{};
    Rest::QRestClient mClient{};
    Workflow::RestSessionDownloader mSessionDownloader{mClient};
    Storage::SqliteSessionDatabase mDatabase{LIBRARY_FILE};
    MainWindowModel mMainWindowModel{mSessionDownloader, mDatabase};
};

} // namespace LaptimerCore::SessionDl

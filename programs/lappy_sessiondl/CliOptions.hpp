// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <QHostAddress>

namespace LaptimerCore::SessionDl
{

class CliOptions
{
public:
    CliOptions(int argc, char** argv) noexcept;

    QHostAddress getHostAddress() const noexcept;

    quint16 getPort() const noexcept;

    bool deleteSessions() const noexcept;

private:
    QHostAddress mHost;
    quint16 mPort{0};
    bool mDeleteSessions{false};
};

} // namespace LaptimerCore::SessionDl

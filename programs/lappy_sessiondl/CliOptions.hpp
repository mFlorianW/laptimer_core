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

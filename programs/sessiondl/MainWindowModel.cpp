#include "MainWindowModel.hpp"

namespace LaptimerCore::SessionDl
{

MainWindowModel::~MainWindowModel() noexcept = default;

QString MainWindowModel::getHostAddress() const noexcept
{
    return mHostAddress.toString();
}

void MainWindowModel::setHostAddress(const QString &hostAddress)
{
    const auto newHost = QHostAddress{hostAddress};
    if (mHostAddress != newHost)
    {
        mHostAddress = newHost;
        Q_EMIT hostAddressChanged();
    }
}

void MainWindowModel::setHostAddress(const QHostAddress &hostAddress)
{
    if (mHostAddress != hostAddress)
    {
        mHostAddress = hostAddress;
        Q_EMIT hostAddressChanged();
    }
}

QString MainWindowModel::getHostPort() const noexcept
{
    return QString::number(mHostPort);
}

void MainWindowModel::setHostPort(const QString &hostPort)
{
    const auto newPort = hostPort.toShort();
    if (mHostPort != newPort)
    {
        mHostPort = newPort;
        Q_EMIT hostPortChanged();
    }
}

void MainWindowModel::setHostPort(quint16 hostPort)
{
    if (mHostPort != hostPort)
    {
        mHostPort = hostPort;
        Q_EMIT hostPortChanged();
    }
}

} // namespace LaptimerCore::SessionDl

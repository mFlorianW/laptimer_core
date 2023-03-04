#pragma once

#include <QHostAddress>
#include <QObject>

namespace LaptimerCore::SessionDl
{
class MainWindowModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindowModel)

    Q_PROPERTY(QString hostAddress READ getHostAddress WRITE setHostAddress NOTIFY hostAddressChanged)

    Q_PROPERTY(QString hostPort READ getHostPort WRITE setHostPort NOTIFY hostPortChanged)
public:
    using QObject::QObject;
    ~MainWindowModel() noexcept override;

    [[nodiscard]] QString getHostAddress() const noexcept;
    void setHostAddress(const QString &hostAddress);
    void setHostAddress(const QHostAddress &hostAddress);

    [[nodiscard]] QString getHostPort() const noexcept;
    void setHostPort(const QString &hostPort);
    void setHostPort(quint16 hostPort);

Q_SIGNALS:
    void hostAddressChanged();
    void hostPortChanged();

private:
    QHostAddress mHostAddress;
    quint16 mHostPort{0};
};
} // namespace LaptimerCore::SessionDl

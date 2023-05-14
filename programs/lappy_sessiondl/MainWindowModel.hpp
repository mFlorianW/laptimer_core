#pragma once

#include <QHostAddress>
#include <QObject>
#include <QRestClient.hpp>
#ifndef Q_MOC_RUN
#include <ISessionDatabase.hpp>
#include <RestSessionDownloader.hpp>
#endif

namespace LaptimerCore::SessionDl
{
class MainWindowModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindowModel)

    Q_PROPERTY(QString hostAddress READ getHostAddress WRITE setHostAddress NOTIFY hostAddressChanged)

    Q_PROPERTY(QString hostPort READ getHostPort WRITE setHostPort NOTIFY hostPortChanged)

    Q_PROPERTY(QString logMessage READ getLogMessage NOTIFY logMessageChanged)
public:
    MainWindowModel(Workflow::ISessionDownloader &downloader, Storage::ISessionDatabase &database) noexcept;
    ~MainWindowModel() noexcept override;

    [[nodiscard]] QString getHostAddress() const noexcept;
    void setHostAddress(const QString &hostAddress);
    void setHostAddress(const QHostAddress &hostAddress);

    [[nodiscard]] QString getHostPort() const noexcept;
    void setHostPort(const QString &hostPort);
    void setHostPort(quint16 hostPort);

    Q_INVOKABLE void startSessionDownload() noexcept;

    QString getLogMessage() const noexcept;

Q_SIGNALS:
    void hostAddressChanged();
    void hostPortChanged();
    void logMessageChanged();

private Q_SLOTS:
    void clearLog() noexcept;
    void appendToLog(const QString &message) noexcept;

private:
    QHostAddress mHostAddress;
    quint16 mHostPort{0};
    QString mDownloadLog;
    Workflow::ISessionDownloader &mSessionDownloader;
    Storage::ISessionDatabase &mSessionDatabase;
};
} // namespace LaptimerCore::SessionDl

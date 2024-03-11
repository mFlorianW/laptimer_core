#include "CliOptions.hpp"
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>

namespace LaptimerCore::SessionDl
{

CliOptions::CliOptions(int argc, char** argv) noexcept
{
    auto const ipOption = QCommandLineOption{{QStringLiteral("i"), QStringLiteral("ip")},
                                             QStringLiteral("IP address of the laptimer."),
                                             QStringLiteral("ip")};
    auto const portOption = QCommandLineOption{{QStringLiteral("p"), QStringLiteral("port")},
                                               QStringLiteral("Port number of the laptimer."),
                                               QStringLiteral("port")};
    auto const deleteOption = QCommandLineOption{{QStringLiteral("d"), QStringLiteral("delete")},
                                                 QStringLiteral("Delete the sessions after download.")};

    auto parser = QCommandLineParser{};
    parser.setApplicationDescription(QStringLiteral("Lappy session downloader"));
    parser.addHelpOption();
    parser.addOptions({ipOption, portOption, deleteOption});

    parser.addPositionalArgument(
        QStringLiteral("sessions"),
        QStringLiteral(
            "White space list of sessions that shall be downloaded. Empty list means download all sessions."));

    parser.process(*QCoreApplication::instance());

    if (parser.isSet(ipOption)) {
        mHost = QHostAddress(parser.value(ipOption));
        if (mHost.isNull()) {
            qInfo() << "Invalid IP Address passed.";
            parser.showHelp(255);
        }
    } else {
        mHost = QHostAddress{"192.168.4.1"};
    }

    if (parser.isSet(portOption)) {
        bool ok = false;
        mPort = parser.value(portOption).toUInt(&ok);
        if (!ok) {
            qInfo() << "Invalid port number passed.";
            parser.showHelp(255);
        }
    } else {
        mPort = 80;
    }

    if (parser.isSet(deleteOption)) {
        mDeleteSessions = true;
    }
}

QHostAddress CliOptions::getHostAddress() const noexcept
{
    return mHost;
}

quint16 CliOptions::getPort() const noexcept
{
    return mPort;
}

bool CliOptions::deleteSessions() const noexcept
{
    return mDeleteSessions;
}

} // namespace LaptimerCore::SessionDl

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "CliOptions.hpp"
#include "LappySessionDownloader.hpp"
#include <QApplication>
#include <QTimer>
#include <SignalDispatcher.hpp>

int main(int argc, char** argv)
{
    QApplication app{argc, argv};
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    auto const options = LaptimerCore::SessionDl::CliOptions{argc, argv};

    // LaptimerCore::SessionDl::CliOptions opts{argc, argv};
    auto const sDl = LaptimerCore::SessionDl::LappySessionDownloader{options.getHostAddress(), options.getPort()};
    sDl.show();

    auto lappyCoreSignalDispatcher = LaptimerCore::System::SignalDispatcher{};
    auto lappyCoreSignaldispatcherTimer = QTimer{};
    lappyCoreSignaldispatcherTimer.setInterval(std::chrono::milliseconds(1));
    QObject::connect(&lappyCoreSignaldispatcherTimer, &QTimer::timeout, &lappyCoreSignaldispatcherTimer, [&] {
        lappyCoreSignalDispatcher.exec();
    });
    lappyCoreSignaldispatcherTimer.start();

    return app.exec();
}

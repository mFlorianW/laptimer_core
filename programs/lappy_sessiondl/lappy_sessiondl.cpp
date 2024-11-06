// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "CliOptions.hpp"
#include "SessionDownloader.hpp"
#include <EventLoop.hpp>
#include <QApplication>
#include <QEventDispatcher.hpp>
#include <QTimer>

int main(int argc, char** argv)
{
    auto* eventDispatcher = new Rapid::System::Qt::QEventDispatcher{}; // NOLINT(cppcoreguidelines-owning-memory)
    QApplication::setEventDispatcher(eventDispatcher);
    QApplication app{argc, argv};
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    auto const options = Rapid::SessionDl::CliOptions{argc, argv};

    // Rapid::SessionDl::CliOptions opts{argc, argv};
    auto const sDl = Rapid::SessionDl::SessionDownloader{options.getHostAddress(), options.getPort()};
    sDl.show();

    return app.exec();
}

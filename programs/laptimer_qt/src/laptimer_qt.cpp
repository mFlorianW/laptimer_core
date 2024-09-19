// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QApplication>
#include <QEventDispatcher.hpp>
#include <QtShell.hpp>

int main(int argc, char* argv[])
{

    auto* eventDispatcher = new LaptimerCore::System::Qt::QEventDispatcher{}; // NOLINT(cppcoreguidelines-owning-memory)
    QApplication::setEventDispatcher(eventDispatcher);
    QApplication app(argc, argv);
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    auto shell = LaptimerCore::QtShell::QtShell{};
    shell.show();

    return app.exec();
}

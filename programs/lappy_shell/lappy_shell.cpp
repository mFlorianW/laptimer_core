#include "LappyShell.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app{argc, argv};
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    auto lappyShell = LaptimerCore::LappyShell::LappyShell{};
    lappyShell.show();

    app.exec();
}

#include <QApplication>
#include <QtShell.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    auto shell = LaptimerCore::QtShell::QtShell{};
    shell.show();

    return app.exec();
}

#include "RestGpsSource.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    auto restgpssource = RestGpsSource{};
    restgpssource.show();

    return app.exec();
}

#define CATCH_CONFIG_MAIN
#include "ApplicationListModel.hpp"
#include "FilePath.hpp"
#include <QAbstractItemModelTester>
#include <catch2/catch.hpp>

using namespace LaptimerCore::LappyShell;

SCENARIO("The ApplicationListModel shall return the correct values for the UI")
{
    auto appModel = ApplicationModel{{CONFIG_APP_PATH}};
    appModel.loadApplications();
    auto listModel = ApplicationListModel{appModel};
    auto modelTester = QAbstractItemModelTester{&listModel};
    WHEN("The values for the UI are requested")
    {
        const auto appName0 = listModel.data(listModel.index(0), ApplicationListModel::AppName).toString();
        const auto appName1 = listModel.data(listModel.index(1), ApplicationListModel::AppName).toString();
        const auto iconUrl0 = listModel.data(listModel.index(0), ApplicationListModel::IconUrl).toString();
        const auto iconUrl1 = listModel.data(listModel.index(1), ApplicationListModel::IconUrl).toString();
        const auto count = listModel.rowCount(QModelIndex{});
        THEN("The correct values shall be returned.")
        {
            REQUIRE(count == 2);
            REQUIRE(appName0.toStdString() == "Testapp1");
            REQUIRE(iconUrl0 == "/usr/share/lappy/test/icon.png");
            REQUIRE(appName1.toStdString() == "Testapp2");
            REQUIRE(iconUrl1 == "/usr/share/lappy/test/icon.png");
        }
    }
}

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
        const auto appName = listModel.data(listModel.index(0), ApplicationListModel::AppName).toString();
        const auto iconUrl = listModel.data(listModel.index(0), ApplicationListModel::IconUrl).toString();
        const auto count = listModel.rowCount(QModelIndex{});
        THEN("The correct values shall be returned.")
        {
            REQUIRE(count == 2);
            REQUIRE(appName == "Testapp1");
            REQUIRE(iconUrl == "/usr/share/lappy/test/icon.png");
        }
    }
}

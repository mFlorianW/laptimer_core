// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DeviceModel.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::LappyShell::Settings;

SCENARIO("The device list model shall provide the header data for the list view.")
{
    GIVEN("An initialized model")
    {
        auto model = DeviceModel{};
        WHEN("Requesting the header")
        {
            auto const headerDataCol0 = model.headerData(0, Qt::Orientation::Horizontal, Qt::DisplayRole);
            auto const headerDataCol1 = model.headerData(1, Qt::Orientation::Horizontal, Qt::DisplayRole);
            auto const headerDataCol2 = model.headerData(2, Qt::Orientation::Horizontal, Qt::DisplayRole);
            auto const headerDataCol3 = model.headerData(3, Qt::Orientation::Horizontal, Qt::DisplayRole);

            THEN("The correct header data is returned")
            {
                REQUIRE(headerDataCol0 == "Name");
                REQUIRE(headerDataCol1 == "IP-Address");
                REQUIRE(headerDataCol2 == "Port");
                REQUIRE(headerDataCol3 == "Default");
            }
        }
    }
}

SCENARIO("The device model shall add new devices to it's interal list")
{
    GIVEN("An initialized model")
    {
        auto model = DeviceModel{};
        WHEN("Adding a device")
        {
            REQUIRE(model.insertRows(0));
            THEN("The row count in the model should be increased and default data shall be returned.")
            {
                REQUIRE(model.rowCount(QModelIndex{}) == 1);
                REQUIRE(model.data(model.index(0, 0), Qt::DisplayRole).toString() == QStringLiteral("Lappy"));
                REQUIRE(model.data(model.index(0, 1), Qt::DisplayRole).toString() == QString("127.0.0.1"));
                REQUIRE(model.data(model.index(0, 2), Qt::DisplayRole).toString() == QString("80"));
                REQUIRE(model.data(model.index(0, 3), Qt::DisplayRole).toBool() == false);
            }
        }

        WHEN("Adding multple devices at once")
        {
            REQUIRE(model.insertRows(0, 5));
            THEN("The row count in the model should be increased and default data shall be returned.")
            {
                REQUIRE(model.rowCount(QModelIndex{}) == 5);
                for (int i = 0; i < 5; ++i) {
                    REQUIRE(model.data(model.index(i, 0), Qt::DisplayRole).toString() == QStringLiteral("Lappy"));
                    REQUIRE(model.data(model.index(i, 3), Qt::DisplayRole).toBool() == false);
                    REQUIRE(model.data(model.index(i, 2), Qt::DisplayRole).toString() == QString("80"));
                    REQUIRE(model.data(model.index(i, 1), Qt::DisplayRole).toString() == QString("127.0.0.1"));
                }
            }
        }
    }
}

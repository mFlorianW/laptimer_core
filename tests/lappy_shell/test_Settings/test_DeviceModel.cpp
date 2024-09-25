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
        auto dListModel = DeviceModel{};
        WHEN("Requesting the header")
        {
            auto const headerDataCol0 = dListModel.headerData(0, Qt::Orientation::Horizontal, Qt::DisplayRole);
            auto const headerDataCol1 = dListModel.headerData(1, Qt::Orientation::Horizontal, Qt::DisplayRole);
            auto const headerDataCol2 = dListModel.headerData(2, Qt::Orientation::Horizontal, Qt::DisplayRole);
            auto const headerDataCol3 = dListModel.headerData(3, Qt::Orientation::Horizontal, Qt::DisplayRole);

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

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <GlobalSettingsReader.hpp>
#include <SettingsMemoryBackend.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::TestHelper;

SCENARIO("The Settings shall load the settings database file path from the provided backend.")
{
    GIVEN("Initialized Settings instance")
    {
        auto settingsBackend = SettingsMemoryBackend();
        REQUIRE(settingsBackend.storeValue(QStringLiteral("dbFilePath"), QStringLiteral("/test/1.db")));
        auto settings = GlobalSettingsReader{&settingsBackend};
        WHEN("The database file path is requested")
        {
            auto const dbFile = settings.getDbFilePath();
            THEN("The correct path shall be returned")
            {
                REQUIRE(dbFile == "/test/1.db");
            }
        }
    }
}

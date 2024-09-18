// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "ApplicationModel.hpp"
#include "FilePath.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::LappyShell;

SCENARIO("The application shall load all applications from a list of folders and return the configs")
{
    auto mdl = ApplicationModel{{CONFIG_APP_PATH}};
    const auto expectedApps = QVector<ApplicationConfig>{{QStringLiteral("Testapp1"),
                                                          QStringLiteral("/usr/bin/test"),
                                                          QStringLiteral("/usr/share/lappy/test/icon.png"),
                                                          ApplicationVersion::fromString("1.2.3")},
                                                         {QStringLiteral("Testapp2"),
                                                          QStringLiteral("/usr/bin/test"),
                                                          QStringLiteral("/usr/share/lappy/test/icon.png"),
                                                          ApplicationVersion::fromString("1.2.3")}};
    WHEN("The applications are loaded")
    {
        mdl.loadApplications();
        THEN("The correct applications configs shall be returned")
        {
            const auto apps = mdl.getApplications();
            REQUIRE(apps.contains(expectedApps[0]));
            REQUIRE(apps.contains(expectedApps[1]));
        }
    }
}

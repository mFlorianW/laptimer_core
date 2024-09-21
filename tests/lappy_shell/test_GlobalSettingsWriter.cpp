// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <GlobalSettingsBackend.hpp>
#include <GlobalSettingsWriter.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::LappyShell;
using namespace LaptimerCore::Common;

namespace
{

class SettingsMemoryBackend : public GlobalSettingsBackend
{
public:
    [[nodiscard]] bool storeValue(QString const& key, QVariant const& value) noexcept override
    {
        mSingleValues.insert(key, value);
        return true;
    }

    [[nodiscard]] QVariant getValue(QString const& key) const noexcept
    {
        return mSingleValues[key];
    }

private:
    QVariantHash mSingleValues;
};

} // namespace

SCENARIO("The Settings shall store the settings database file path.")
{
    GIVEN("Initialized Settings instance")
    {
        auto settingsBackend = SettingsMemoryBackend();
        auto settings = GlobalSettingsWriter{&settingsBackend};
        WHEN("The databease file path is stored.")
        {
            auto const expDbFilePath = QStringLiteral("/test/1.db");
            REQUIRE(settings.storeDatabaseFilePath(expDbFilePath));
            THEN("The stored database file path shall be stored correctly in the backend")
            {
                auto dbFilePath = settingsBackend.getValue("dbFilePath").toString();
                REQUIRE(dbFilePath == expDbFilePath);
            }
        }
    }
}

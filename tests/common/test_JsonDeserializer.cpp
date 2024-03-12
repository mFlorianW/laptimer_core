// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "JsonDeserializer.hpp"
#include "Sessions.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::TestHelper;

TEST_CASE("The JsonDeserializer shall deserialize a valid json string into a SessionData")
{
    auto expectedSession = Sessions::getTestSession();
    auto result = JsonDeserializer::deserializeSessionData(Sessions::getTestSessionAsJson());
    REQUIRE(result.value() == expectedSession);
}

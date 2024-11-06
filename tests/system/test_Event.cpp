// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#define CATCH_CONFIG_MAIN
#include "Event.hpp"
#include <catch2/catch.hpp>

using namespace Rapid::System;

SCENARIO("The Event shall give the type")
{
    GIVEN("A Event")
    {
        auto const event = Event{};
        WHEN("Requesting the type")
        {
            auto const eventType = event.getEventType();
            THEN("The correct type shall be returned")
            {
                REQUIRE(eventType == Event::Type::Unknown);
            }
        }
    }
}

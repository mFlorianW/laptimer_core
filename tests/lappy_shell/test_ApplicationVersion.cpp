#define CATCH_CONFIG_MAIN
#include "ApplicationConfig.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::LappyShell;

SCENARIO("The application version shall be constructable from a string")
{
    const auto expectedVersion = ApplicationVersion{1, 2, 3};
    const auto stringVersion = QString{"1.2.3"};
    WHEN("The application version is created from the string")
    {
        const auto version = ApplicationVersion::fromString(stringVersion);
        THEN("The correct application shall be created.")
        {
            REQUIRE(version == expectedVersion);
        }
    }
}

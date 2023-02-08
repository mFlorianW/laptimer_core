#define CATCH_CONFIG_MAIN
#include "Path.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Rest;

SCENARIO("A path shall give the number of level in the path")
{
    GIVEN("A path with three levels")
    {
        const auto path = Path{"test/path/dup"};
        constexpr auto expectedLevels = 3;

        WHEN("The path levels are requested.")
        {
            const auto levels = path.getDepth();
            THEN("The correct level depth shall be returned")
            {
                REQUIRE(levels == expectedLevels);
            }
        }
    }

    GIVEN("A empty path")
    {
        const auto path = Path{""};
        constexpr auto expectedLevels = 0;

        WHEN("The path level is requested")
        {
            const auto levels = path.getDepth();
            THEN("The correct level of the path shall be returned")
            {
                REQUIRE(levels == expectedLevels);
            }
        }
    }
}

SCENARIO("A path shall give the path elements addressed by the element index")
{
    GIVEN("A path with three levels")
    {
        const auto path = Path{"test/path/dup"};

        WHEN("The path element with index 0 is requested")
        {
            const auto element = path.getEntry(0);
            const auto expectedElement = "test";
            THEN("The correct entry shall be returned")
            {
                REQUIRE(element.has_value() == true);
                REQUIRE(element.value_or("") == expectedElement);
            }
        }

        WHEN("The path element with index 1 is requested")
        {
            const auto element = path.getEntry(1);
            const auto expectedElement = "path";
            THEN("The correct entry shall be returned")
            {
                REQUIRE(element.has_value() == true);
                REQUIRE(element.value_or("") == expectedElement);
            }
        }

        WHEN("The path element with index 2 is requested")
        {
            const auto element = path.getEntry(2);
            const auto expectedElement = "dup";
            THEN("The correct entry shall be returned")
            {
                REQUIRE(element.has_value() == true);
                REQUIRE(element.value_or("") == expectedElement);
            }
        }

        WHEN("A path element with an invalid index is requested")
        {
            const auto element = path.getEntry(100);
            THEN("A nullopt shall be returned")
            {
                REQUIRE(element.has_value() == false);
            }
        }
    }

    GIVEN("A empty Path")
    {
        const auto path = Path{""};
        WHEN("The path element of an empty path is requested")
        {
            const auto element = path.getEntry(2);
            THEN("A nullopt shall be returned")
            {
                REQUIRE(element.has_value() == false);
            }
        }
    }
}

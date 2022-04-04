#define CATCH_CONFIG_MAIN
#include "SessionData.hpp"
#include "Sessions.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The SessionData shall be serialize to a JSON format")
{
    auto session = Sessions::TestSession;

    auto result = session.asJson().as<std::string>();

    REQUIRE(result == Sessions::TestSessionAsJson);
}

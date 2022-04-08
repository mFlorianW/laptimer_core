#define CATCH_CONFIG_MAIN
#include "JsonDeserializer.hpp"
#include "Sessions.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The JsonDeserializer shall deserialize a valid json string into a SessionData")
{
    auto expectedSession = Sessions::TestSession;
    auto result = JsonDeserializer::deserializeSessionData(Sessions::TestSessionAsJson);
    REQUIRE(result.value() == expectedSession);
}

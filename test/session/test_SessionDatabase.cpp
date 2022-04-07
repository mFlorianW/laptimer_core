#define CATCH_CONFIG_MAIN
#include "MemorySessionDatabaseBackend.hpp"
#include "SessionDatabase.hpp"
#include "Sessions.hpp"
#include "Tracks.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Session;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The session database shall serialize the SessionData to JSON and store them")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result = sessionDb.storeSession(Sessions::TestSession);

    REQUIRE(result);
    REQUIRE(backend.loadSessionByIndex(0) == Sessions::TestSessionAsJson);
}

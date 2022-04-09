#define CATCH_CONFIG_MAIN
#include "MemorySessionDatabaseBackend.hpp"
#include "SessionDatabase.hpp"
#include "Sessions.hpp"
#include "Tracks.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Session;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The SessionDatabase shall serialize the SessionData to JSON and store them")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result = sessionDb.storeSession(Sessions::TestSession);

    REQUIRE(result);
    REQUIRE(backend.loadSessionByIndex(1) == Sessions::TestSessionAsJson);
}

TEST_CASE("The SessionDatabase shall store two Sessions with inrcrementing indices")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result1 = sessionDb.storeSession(Sessions::TestSession);
    auto result2 = sessionDb.storeSession(Sessions::TestSession);

    REQUIRE(result1);
    REQUIRE(backend.loadSessionByIndex(1) == Sessions::TestSessionAsJson);

    REQUIRE(result2);
    REQUIRE(backend.loadSessionByIndex(2) == Sessions::TestSessionAsJson);
}

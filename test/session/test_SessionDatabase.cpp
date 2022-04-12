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
    REQUIRE(backend.loadSessionByIndex(0) == Sessions::TestSessionAsJson);
}

TEST_CASE("The SessionDatabase shall return the amout of the stored sessions")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result = sessionDb.storeSession(Sessions::TestSession);

    REQUIRE(result);
    REQUIRE(sessionDb.getSessionCount() == 1);
}

TEST_CASE("The SessionDatabase shall store two different sessions")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result1 = sessionDb.storeSession(Sessions::TestSession);
    auto result2 = sessionDb.storeSession(Sessions::TestSession2);

    REQUIRE(result1);
    REQUIRE(result2);
    REQUIRE(backend.getNumberOfStoredSessions() == 2);
    //    REQUIRE(sessionDb.getSessionCount() == 2);
}

TEST_CASE("The SessionDatabase shall be able to delete a single session.")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result = sessionDb.storeSession(Sessions::TestSession);
    REQUIRE(sessionDb.getSessionCount() == 1);
    REQUIRE(result);

    sessionDb.deleteSession(0);
    REQUIRE(sessionDb.getSessionCount() == 0);
}

TEST_CASE("The SessionDatabase shall load the Session by the given valid index.")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result = sessionDb.storeSession(Sessions::TestSession);
    auto session = sessionDb.getSessionByIndex(0);

    REQUIRE(result);
    REQUIRE(session);
    REQUIRE(session.value() == Sessions::TestSession);
}

TEST_CASE("The SessionDatabase shall store an already stored session under the same index.")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};

    auto result1 = sessionDb.storeSession(Sessions::TestSession);
    auto result2 = sessionDb.storeSession(Sessions::TestSession);

    REQUIRE(result1);
    REQUIRE(result2);
    REQUIRE(sessionDb.getSessionCount() == 1);
}

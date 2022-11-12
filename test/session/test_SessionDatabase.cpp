#define CATCH_CONFIG_MAIN
#include "MemorySessionDatabaseBackend.hpp"
#include "SessionDatabase.hpp"
#include "Sessions.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Session;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::Test::Dummy;

TEST_CASE("The SessionDatabase shall serialize the SessionData to JSON, store them and emit the signal new session is "
          "stored.")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};
    auto sessionStoredSpy = false;
    auto sessionStoredIndex = 99;
    sessionDb.sessionAdded.connect([&](std::size_t index) {
        sessionStoredSpy = true;
        sessionStoredIndex = index;
    });
    auto result = sessionDb.storeSession(Sessions::TestSession);

    REQUIRE(result);
    REQUIRE(sessionStoredSpy);
    REQUIRE(sessionStoredIndex == 0);
    REQUIRE(backend.loadSessionByIndex(0) == Sessions::TestSessionAsJson);
}

TEST_CASE("The SessionDatabase shall return the amount of the stored sessions")
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
    REQUIRE(sessionDb.getSessionCount() == 2);
    REQUIRE(sessionDb.getSessionByIndex(0) == Sessions::TestSession);
    REQUIRE(sessionDb.getSessionByIndex(1) == Sessions::TestSession2);
}

TEST_CASE("The SessionDatabase shall be able to delete a single session and emit the signal session deleted.")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};
    auto sessionDeletedSpy = false;
    auto sessionDeletedIndex = 99;

    auto result = sessionDb.storeSession(Sessions::TestSession);
    sessionDb.sessionDeleted.connect([&](std::size_t index) {
        sessionDeletedSpy = true;
        sessionDeletedIndex = index;
    });
    REQUIRE(sessionDb.getSessionCount() == 1);
    REQUIRE(result);

    sessionDb.deleteSession(0);
    REQUIRE(sessionDb.getSessionCount() == 0);
    REQUIRE(sessionDeletedSpy);
    REQUIRE(sessionDeletedIndex == 0);
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

TEST_CASE("The SessionDatabase shall store an already stored session under the same index. and shall emit the signal "
          "session updated.")
{
    auto backend = MemorySessionDatabaseBackend{};
    auto sessionDb = SessionDatabase{backend};
    auto sessionUpdatedSpy = false;
    auto sessionUpdatedIndex = 99;
    sessionDb.sessionUpdated.connect([&](std::size_t index) {
        sessionUpdatedSpy = true;
        sessionUpdatedIndex = index;
    });

    auto result1 = sessionDb.storeSession(Sessions::TestSession);
    auto result2 = sessionDb.storeSession(Sessions::TestSession2);
    auto result3 = sessionDb.storeSession(Sessions::TestSession2);

    REQUIRE(result1);
    REQUIRE(result2);
    REQUIRE(result3);
    REQUIRE(sessionDb.getSessionCount() == 2);
    REQUIRE(sessionDb.getSessionByIndex(0) == Sessions::TestSession);
    REQUIRE(sessionDb.getSessionByIndex(1) == Sessions::TestSession2);
    REQUIRE(sessionUpdatedSpy);
    REQUIRE(sessionUpdatedIndex == 1);
}

#define CATCH_CONFIG_MAIN
#include "MemorySessionDatabaseBackend.hpp"
#include "SessionDatabase.hpp"
#include "SessionEndpoint.hpp"
#include "Sessions.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Rest;
using namespace LaptimerCore::TestHelper;
using namespace LaptimerCore::Storage;

SCENARIO("Calling the Session on the folder /sessions shall return the session count")
{
    GIVEN("A session endpoint with two session")
    {
        auto dbBackend = MemorySessionDatabaseBackend{};
        auto db = SessionDatabase{dbBackend};
        auto endpoint = SessionEndpoint{db};
        db.storeSession(Sessions::getTestSession());
        db.storeSession(Sessions::getTestSession2());

        WHEN("Requesting the top folder /sessions shall return the session count")
        {
            auto request = RestRequest{RequestType::Get, "/sessions"};
            endpoint.handleRestRequest(request);
            THEN("Give the correct session id list.")
            {
                auto expectedReturnBody = std::string{R"({"count":2})"};
                REQUIRE(request.getReturnBody() == expectedReturnBody);
            }
        }
    }
}

SCENARIO("Calling the Session endpoint on a specific path under /sessions/{n} shall return the session")
{
    GIVEN("A session endpoint with one session")
    {
        auto dbBackend = MemorySessionDatabaseBackend{};
        auto db = SessionDatabase{dbBackend};
        auto endpoint = SessionEndpoint{db};
        auto asyncResult = db.storeSession(Sessions::getTestSession());
        asyncResult->waitForFinished();

        WHEN("Requesting the a specifc under /sessions/0 shall return the session")
        {
            auto request = RestRequest{RequestType::Get, "/sessions/0"};
            endpoint.handleRestRequest(request);
            THEN("Give the correct session id list.")
            {
                auto expectedReturnBody = Sessions::getTestSessionAsJson();
                REQUIRE(request.getReturnBody() == expectedReturnBody);
            }
        }
    }
}

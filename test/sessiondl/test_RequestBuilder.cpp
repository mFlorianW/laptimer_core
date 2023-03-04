#define CATCH_CONFIG_MAIN
#include "RequestBuilder.hpp"
#include <QHostAddress>
#include <QNetworkRequest>
#include <catch2/catch.hpp>
#include <utility>

using namespace LaptimerCore::SessionDl;

SCENARIO("The RequestBuilder shall create a GET for a specific session.")
{
    GIVEN("The RequestBuilder")
    {
        auto expectedRequest = QNetworkRequest{};
        expectedRequest.setUrl({"http://192.168.4.1:80/session/12"});
        WHEN("A session request shall be created")
        {
            const auto request = RequestBuilder{QUrl{"http://192.168.4.1:80"}}.createSessionRequest(12);
            THEN("The correct request shall be created.")
            {
                REQUIRE(request == expectedRequest);
            }
        }
    }
}

SCENARIO("The RequestBuilder shall create a GET request for the amount of stored sessions")
{
    GIVEN("The RequestBuilder")
    {
        auto reqBuilder = RequestBuilder{QUrl{"http://192.168.4.1:80"}};
        WHEN("The session amount request is created")
        {
            const auto request = reqBuilder.createSessionCountRequest();
            auto expectedRequest = QNetworkRequest{};
            expectedRequest.setUrl(QUrl{"http://192.168.4.1:80/session"});
            THEN("The correct request shall be created")
            {
                REQUIRE(request == expectedRequest);
            }
        }
    }
}

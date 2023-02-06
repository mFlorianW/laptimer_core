#define CATCH_CONFIG_MAIN
#include "GpsEndpoint.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Rest;
using namespace LaptimerCore::Common;

namespace
{
const auto request = std::string{"{\"date\":\"01.00.0123\","
                                 "\"latitude\":\"52.02739715576172\","
                                 "\"longitude\":\"11.278840065002441\","
                                 "\"time\":\"17:19:05.045\"}"};

} // namespace

TEST_CASE("The GpsEndpoint shall parse the JSON RestRequest and shall update the PositionDateTime Property")
{
    auto restRequest = RestRequest{};
    auto source = GpsEndpoint{};
    auto expectedResult = PositionDateTimeData{};
    expectedResult.setDate({"01.00.0123"});
    expectedResult.setTime({"17:19:05.045"});
    expectedResult.setPosition({52.02739715576172, 11.278840065002441});

    restRequest.setRequestBody(request);
    const auto handleResult = source.handleRestRequest(restRequest);

    REQUIRE(handleResult == RequestHandleResult::Ok);
    REQUIRE(source.positionTimeData.get() == expectedResult);
}

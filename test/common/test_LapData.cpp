#define CATCH_CONFIG_MAIN
#include "LapData.hpp"
#include "Timestamp.hpp"
#include <ArduinoJson.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::Common;

/*
 *
{
"laptime":"00:00.000",
"sectors":[
    {
     "sector1":"00:00.000"
    },
    {
     "sector2":"00:00.000"
    },
    {
     "sector3":"00:00.000"
    },
    {
     "sector4":"00:00.000"
    }
]
}
 */

TEST_CASE("The lap data shall serialize the laptime without sector into a json document.")
{
    constexpr char expectedResult[] = "{\"laptime\":\"00:01:35.123\"}";
    Timestamp lapTime;
    lapTime.setHour(0);
    lapTime.setMinute(1);
    lapTime.setSecond(35);
    lapTime.setFractionalOfSecond(123);
    LapData lap;
    lap.setLaptime(lapTime);

    std::string result;
    ArduinoJson::serializeJson(lap.serialize(), result);

    REQUIRE(result == expectedResult);
}

#define CATCH_CONFIG_MAIN
#include "ConstantVelocityPositionDateTimeProvider.hpp"
#include "SignalDispatcher.hpp"
#include <PositionData.hpp>
#include <catch2/catch.hpp>
#include <thread>

using namespace LaptimerCore::Positioning;
using namespace LaptimerCore::Common;
using namespace LaptimerCore::System;

TEST_CASE("The ConstantVelocityPositionDateTimeProvider shall interpolate the position between two points if the given "
          "point data is insufficent.")
{
    auto dispatcher = SignalDispatcher{};
    auto const timeToSleep = std::chrono::milliseconds(100);
    auto positions = std::vector<PositionData>{{52.026649, 11.282535}, {52.026751, 11.282047}, {52.026807, 11.281746}};
    auto lastPosition = PositionDateTimeData{};

    auto source = ConstantVelocityPositionDateTimeProvider{positions};
    source.positionTimeData.valueChanged().connect([&]() {
        lastPosition = source.positionTimeData.get();
    });
    source.setVelocityInMeterPerSecond(2.77778);
    source.start();

    std::this_thread::sleep_for(timeToSleep);
    dispatcher.exec();
    auto expectedPosition = PositionDateTimeData{{52.026649, 11.282535}, {}, {}};
    REQUIRE(lastPosition.getPosition().getLatitude() == expectedPosition.getPosition().getLatitude());
    REQUIRE(lastPosition.getPosition().getLongitude() == expectedPosition.getPosition().getLongitude());

    std::this_thread::sleep_for(timeToSleep);
    dispatcher.exec();
    expectedPosition = PositionDateTimeData{{52.02665, 11.28253}, {}, {}};
    REQUIRE(lastPosition.getPosition().getLatitude() == expectedPosition.getPosition().getLatitude());
    REQUIRE(lastPosition.getPosition().getLongitude() == Approx(expectedPosition.getPosition().getLongitude()));
}

TEST_CASE("The ConstantVelocityPositionDateTimeProvider shall provide every 100ms a new position.")
{
    auto dispatcher = SignalDispatcher{};
    auto const timeToSleep = std::chrono::milliseconds(100);
    std::uint8_t updateCounter = 0;
    auto positions = std::vector<PositionData>{{52.026649, 11.282535}, {52.026751, 11.282047}, {52.026807, 11.281746}};
    auto source = ConstantVelocityPositionDateTimeProvider{positions};
    source.setVelocityInMeterPerSecond(2.77778);
    source.positionTimeData.valueChanged().connect([&]() {
        ++updateCounter;
    });
    source.start();

    std::this_thread::sleep_for(timeToSleep);
    dispatcher.exec();
    REQUIRE(updateCounter == 1);

    std::this_thread::sleep_for(timeToSleep);
    dispatcher.exec();
    REQUIRE(updateCounter == 2);

    source.stop();
    std::this_thread::sleep_for(timeToSleep);
    dispatcher.exec();
    REQUIRE(updateCounter == 2);
}

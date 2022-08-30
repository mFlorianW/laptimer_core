#define CATCH_CONFIG_MAIN
#include "ActiveSessionWorkflow.hpp"
#include "Laptimer.hpp"
#include "MemorySessionDatabaseBackend.hpp"
#include "PositionDateTimeProvider.hpp"
#include "SessionDatabase.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Workflow;
using namespace LaptimerCore::Test::Dummy;
using namespace LaptimerCore::Session;
using namespace LaptimerCore::Common;

TEST_CASE("The ActiveSessionWorkflow shall not do return a session when start isn't called")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};

    REQUIRE(!actSessWf.getSession());
}

TEST_CASE("The ActiveSessionWorkflow shall return a session when start called")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};

    actSessWf.startActiveSession();

    REQUIRE(actSessWf.getSession());
}

TEST_CASE("The ActiveSessionWorkflow shall store a lap in the database when the laptimer emits lap finished")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};

    actSessWf.startActiveSession();
    lp.lapFinished.emit();

    REQUIRE(sdb.getSessionCount() == 1);
}

TEST_CASE("The ActiveSessionWorkflow shall not return a valid session when stop is called.")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};

    actSessWf.startActiveSession();

    REQUIRE(actSessWf.getSession());

    actSessWf.stopActiveSession();

    REQUIRE(!actSessWf.getSession());
}

TEST_CASE("The ActiveSessionWorkflow shall update the round sector time property when the laptimer notifes that sector "
          "is finished.")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};
    auto expectedSectorTime = Timestamp{"00:00:12.123"};

    actSessWf.startActiveSession();
    lp.lastSectorTime = Timestamp{"00:00:12.123"};
    lp.sectorFinished.emit();

    REQUIRE(actSessWf.lastSectorTime.get() == expectedSectorTime);
}

TEST_CASE("The ActiveSessionWorkflow shall store the laptime when finished.")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};
    auto expectedLap = LapData{Timestamp{"00:23:13.123"}};

    actSessWf.startActiveSession();
    lp.lastLapTime = Timestamp{"00:23:13.123"};
    lp.lapFinished.emit();

    REQUIRE(actSessWf.getSession()->getLaps().size() == 1);
    REQUIRE(actSessWf.getSession()->getLaps().at(0) == expectedLap);
}

TEST_CASE("The ActiveSessionWorkflow shall update the round laptime property when the laptimer notifes that the "
          "is finished.")
{
    auto lp = Laptimer{};
    auto dp = PositionDateTimeProvider{};
    auto dbb = MemorySessionDatabaseBackend{};
    auto sdb = SessionDatabase{dbb};
    auto actSessWf = ActiveSessionWorkflow{dp, lp, sdb};
    auto expectedLaptime = Timestamp{"00:00:12.123"};

    actSessWf.startActiveSession();
    lp.lastLapTime = Timestamp{"00:00:12.123"};
    lp.lapFinished.emit();

    REQUIRE(actSessWf.lastLaptime.get() == expectedLaptime);
}

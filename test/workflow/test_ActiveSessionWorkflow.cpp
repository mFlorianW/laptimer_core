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

TEST_CASE("The ActiveSessionWorkflow shall not do anything when stop is called")
{
}

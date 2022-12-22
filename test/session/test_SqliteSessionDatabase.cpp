#define CATCH_CONFIG_MAIN
#include "Sessions.hpp"
#include "SqliteSessionDatabase.hpp"
#include <SqliteDatabaseTestHelper.hpp>
#include <catch2/catch.hpp>

using namespace LaptimerCore::Session;
using namespace LaptimerCore::TestHelper;
using namespace LaptimerCore::TestHelper::SqliteDatabaseTestHelper;

namespace
{
class TestSqliteSessionDatabaseEventListener : public Catch::TestEventListenerBase
{
    using Catch::TestEventListenerBase::TestEventListenerBase;

    void testCaseStarting(const Catch::TestCaseInfo &testInfo) override
    {
        // For the case the test crashes.
        if (std::filesystem::exists(getTestDatabseFolder()) == true)
        {
            std::filesystem::remove_all(getTestDatabseFolder());
        }
        REQUIRE(std::filesystem::create_directory(getTestDatabseFolder()) == true);
        const auto cleanDbFile = getWorkingDir() + "/test_session.db";
        REQUIRE(std::filesystem::copy_file(cleanDbFile, getTestDatabseFile("test_session.db")) == true);
    }

    void testCaseEnded(const Catch::TestCaseStats &testCaseStatu) override
    {
        REQUIRE(std::filesystem::remove(getTestDatabseFile("test_session.db")) == true);
    }
};
} // namespace

CATCH_REGISTER_LISTENER(TestSqliteSessionDatabaseEventListener)

TEST_CASE("The SqliteSessionDatabase shall store as session and shall emit the session added signal.")
{
    auto db = SqliteSessionDatabase{getTestDatabseFile("test_session.db")};
    auto sessionAddedSignalEmitted = false;
    auto addedIndex = std::size_t{123456};
    db.sessionAdded.connect([&sessionAddedSignalEmitted, &addedIndex](std::size_t index) {
        sessionAddedSignalEmitted = true;
        addedIndex = index;
    });

    const auto insertResult = db.storeSession(Sessions::getTestSession3());
    REQUIRE(insertResult == true);
    REQUIRE(addedIndex == 0);
    REQUIRE(sessionAddedSignalEmitted == true);
}

TEST_CASE("The SqliteSessionDatabase shall store a session and the session shall be directly read again.")
{
    auto db = SqliteSessionDatabase{getTestDatabseFile("test_session.db")};
    auto addedIndex = std::size_t{123456};
    db.sessionAdded.connect([&addedIndex](std::size_t index) { addedIndex = index; });

    const auto insertResult = db.storeSession(Sessions::getTestSession3());
    REQUIRE(insertResult == true);
    REQUIRE(addedIndex == 0);

    const auto readResult = db.getSessionByIndex(addedIndex);
    REQUIRE(readResult.has_value() == true);
    REQUIRE(readResult.value() == Sessions::getTestSession3());
}

TEST_CASE("The SqliteSessionDatabase shall store a already stored session under the same index and shall emit session "
          "updated.")
{
    auto db = SqliteSessionDatabase{getTestDatabseFile("test_session.db")};
    auto updatedIndex = std::size_t{123456};
    db.sessionUpdated.connect([&updatedIndex](std::size_t index) { updatedIndex = index; });

    auto insertResult = db.storeSession(Sessions::getTestSession3());
    REQUIRE(insertResult == true);

    auto lapData = LaptimerCore::Common::LapData{};
    lapData.addSectorTimes({{"00:23:32.003"}, {"00:23:32.004"}, {"00:23:32.005"}});
    auto session = Sessions::getTestSession3();
    session.addLap(lapData);

    insertResult = db.storeSession(session);
    REQUIRE(insertResult == true);
    REQUIRE(updatedIndex == 0);
    REQUIRE(db.getSessionByIndex(0) == session);
}

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

    auto insertResult = db.storeSession(Sessions::getTestSession3());
    REQUIRE(insertResult == true);
    REQUIRE(addedIndex == 0);
    REQUIRE(sessionAddedSignalEmitted == true);

    insertResult = db.storeSession(Sessions::getTestSession4());
    REQUIRE(insertResult == true);
    REQUIRE(addedIndex == 1);
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
    insertResult = db.storeSession(Sessions::getTestSession4());
    REQUIRE(insertResult == true);

    auto lapData = LaptimerCore::Common::LapData{};
    lapData.addSectorTimes({{"00:23:32.003"}, {"00:23:32.004"}, {"00:23:32.005"}});
    auto session1 = Sessions::getTestSession3();
    session1.addLap(lapData);
    auto session2 = Sessions::getTestSession4();
    session2.addLap(lapData);

    insertResult = db.storeSession(session1);
    REQUIRE(insertResult == true);
    REQUIRE(updatedIndex == 0);
    REQUIRE(db.getSessionByIndex(0) == session1);

    insertResult = db.storeSession(session2);
    REQUIRE(insertResult == true);
    REQUIRE(updatedIndex == 1);
    REQUIRE(db.getSessionByIndex(1) == session2);
}

TEST_CASE("The SqliteSessionDatabase shall gives the number of stored sessions and should return the correct session "
          "for that index.")
{
    auto db = SqliteSessionDatabase{getTestDatabseFile("test_session.db")};
    const auto session1 = Sessions::getTestSession3();
    const auto session2 = Sessions::getTestSession4();
    constexpr auto expectedSessionCount = 2;

    // Prepare database.
    auto storeResult = db.storeSession(session1);
    REQUIRE(storeResult == true);
    storeResult = false;
    storeResult = db.storeSession(session2);
    REQUIRE(storeResult == true);

    const auto sessionCount = db.getSessionCount();
    REQUIRE(sessionCount == expectedSessionCount);

    REQUIRE(db.getSessionByIndex(0).value() == session1);
    REQUIRE(db.getSessionByIndex(1).value() == session2);
    REQUIRE(db.getSessionByIndex(2) == std::nullopt);
}

TEST_CASE(
    "The SqliteSessionDatabase shall delete a session under the index and shall emit the sessionDelete signal with the "
    "index.")
{
    auto db = SqliteSessionDatabase{getTestDatabseFile("test_session.db")};
    const auto session1 = Sessions::getTestSession3();
    const auto session2 = Sessions::getTestSession4();
    auto deletedIndex = std::size_t{123456};
    constexpr auto indexToDelete = 1;
    db.sessionDeleted.connect([&deletedIndex](std::size_t index) { deletedIndex = index; });

    // Prepare database.
    auto storeResult = db.storeSession(session1);
    REQUIRE(storeResult == true);
    storeResult = false;
    storeResult = db.storeSession(session2);
    REQUIRE(storeResult == true);
    REQUIRE(db.getSessionCount() == 2);

    db.deleteSession(indexToDelete);
    REQUIRE(deletedIndex == indexToDelete);
    REQUIRE(db.getSessionCount() == 1);
}

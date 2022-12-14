#define CATCH_CONFIG_MAIN
#include "SqliteTrackDatabase.hpp"
#include <catch2/catch.hpp>
#include <filesystem>

using namespace LaptimerCore::TrackManagement;

namespace
{
std::string getWorkingDir()
{
    auto buffer = std::array<char, 512>{0};
    auto *bufferPtr = getcwd(&buffer.at(0), buffer.size());
    if (bufferPtr == nullptr)
    {
        FAIL("Unable to get the database folder.");
    }

    return std::string{&buffer.at(0)};
}

std::string getTestDatabseFolder()
{
    auto dbDir = getWorkingDir() + "/database";
    return dbDir;
}

std::string getTestDatabseFile()
{
    return getTestDatabseFolder() + "/trackmanagement_test.db";
}
} // namespace

class SqliteDatabaseTestEventlistener : public Catch::TestEventListenerBase
{
public:
    using Catch::TestEventListenerBase::TestEventListenerBase;

    void testCaseStarting(const Catch::TestCaseInfo &testInfo) override
    {
        // For the case the test crashes.
        if (std::filesystem::exists(getTestDatabseFolder()) == true)
        {
            REQUIRE(std::filesystem::remove_all(getTestDatabseFolder()) == true);
        }
        REQUIRE(std::filesystem::create_directory(getTestDatabseFolder()) == true);
        const auto cleanDbFile = getWorkingDir() + "/test_trackmanagement.db";
        REQUIRE(std::filesystem::copy_file(cleanDbFile, getTestDatabseFile()) == true);
    }

    void testCaseEnded(const Catch::TestCaseStats &testCaseStats) override
    {
        REQUIRE(std::filesystem::remove(getTestDatabseFile()) == true);
    }
};
CATCH_REGISTER_LISTENER(SqliteDatabaseTestEventlistener);

TEST_CASE("The SqliteDatabaseTrackDatabase shall return the number of stored tracks.")
{
    auto trackDb = SqliteTrackDatabase{getTestDatabseFile()};
    REQUIRE(trackDb.getTrackCount() == 2);
}

TEST_CASE("The SqliteDatabaseTrackDatabase shall return all stored tracks.")
{
    auto trackDb = SqliteTrackDatabase{getTestDatabseFile()};

    auto osl = LaptimerCore::Common::TrackData{};
    osl.setTrackName("Oschersleben");
    osl.setStartline({52.0271, 11.2804});
    osl.setFinishline({52.0270889, 11.2803483});
    osl.setSections({{52.0298205, 11.2741851}, {52.0299681, 11.2772076}});

    auto assen = LaptimerCore::Common::TrackData{};
    assen.setTrackName("Assen");
    assen.setFinishline({52.962324, 6.524115});
    assen.setSections({{52.959453, 6.525305}, {52.955628, 6.512773}});

    const auto tracks = trackDb.getTracks();

    REQUIRE_THAT(tracks, Catch::Matchers::UnorderedEquals(std::vector<LaptimerCore::Common::TrackData>{osl, assen}));
}

#define CATCH_CONFIG_MAIN
#include <FileSystemSessionDatabaseBackend.hpp>
#include <Sessions.hpp>
#include <catch2/catch.hpp>
#include <filesystem>
#include <unistd.h>

using namespace LaptimerCore::Session;
using namespace LaptimerCore::Test::Dummy;

namespace
{

std::string getTestDatabseFolder()
{
    std::array<char, 512> buffer;

    auto *bufferPtr = getcwd(&buffer.at(0), buffer.size());
    if (bufferPtr == nullptr)
    {
        FAIL("Unable to get the database folder.");
    }

    auto dbDir = std::string{&buffer.at(0)} + "/database";

    return dbDir;
}

class FileSystemTestEventListener : public Catch::TestEventListenerBase
{
public:
    using Catch::TestEventListenerBase::TestEventListenerBase;

    void testCaseStarting(const Catch::TestCaseInfo &testInfo) override
    {
        auto dbFolder = getTestDatabseFolder();

        // For the case the test crashes.
        if (std::filesystem::exists(dbFolder))
        {
            std::filesystem::remove_all(dbFolder);
        }

        std::filesystem::create_directory(dbFolder);
    }

    void testCaseEnded(const Catch::TestCaseStats &testCaseStats) override
    {
        auto dbFolder = getTestDatabseFolder();
        std::filesystem::remove_all(dbFolder);
    }
};
CATCH_REGISTER_LISTENER(FileSystemTestEventListener);

} // namespace

TEST_CASE("The FileSystemSessionDatabaseBackend shall store the first session under session1.json")
{
    auto dbFolder = getTestDatabseFolder();
    auto fsBackend = FileSystemSessionDatabaseBackend{dbFolder};
    auto expectedFilePath = std::filesystem::path{dbFolder + "/session1.json"};

    REQUIRE(fsBackend.storeSession(1, Sessions::TestSessionAsJson));
    REQUIRE(std::filesystem::exists(expectedFilePath));
}

TEST_CASE("The FileSystemSessionDatabaseBackend store shall fail when database folder doesn't exists.")
{
    auto dbFolder = getTestDatabseFolder();
    auto fsBackend = FileSystemSessionDatabaseBackend{dbFolder};
    auto expectedFilePath = std::filesystem::path{dbFolder + "/session1.json"};

    std::filesystem::remove_all(dbFolder);

    REQUIRE(!fsBackend.storeSession(1, Sessions::TestSessionAsJson));
}

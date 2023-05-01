#define CATCH_CONFIG_MAIN
#include "RestSessionDownloader.hpp"
#include "RestSessionDownloaderClient.hpp"
#include <catch2/catch.hpp>

using namespace LaptimerCore::Workflow;
using namespace LaptimerCore::TestHelper;

SCENARIO("The RestSessionDownload shall fetch the stored session count on the laptimer")
{
    GIVEN("A setuped RestSessionDownload")
    {
        auto restClient = RestSessionDownloaderClient{};
        auto rDl = RestSessionDownloader{restClient};
        auto fetchSignalEmitted = false;
        auto fetchStatus = DownloadResult::Error;
        rDl.sessionCountFetched.connect([&](DownloadResult result) {
            fetchSignalEmitted = true;
            fetchStatus = DownloadResult::Ok;
        });

        WHEN("Fetching the SessionCount on the device")
        {
            rDl.fetchSessionCount();
            THEN("Then the correct session count shall be returned.")
            {
                constexpr auto sessionCount = std::size_t{2};
                REQUIRE(fetchSignalEmitted);
                REQUIRE(fetchStatus == DownloadResult::Ok);
                REQUIRE(rDl.getSessionCount() == sessionCount);
            }
        }
    }
}

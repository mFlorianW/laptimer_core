#ifndef LAPTIMERCORE_TEST_DUMMY_SQLITEDATABASETESTEVENTLISTENER_HPP
#define LAPTIMERCORE_TEST_DUMMY_SQLITEDATABASETESTEVENTLISTENER_HPP
#define CATCH_CONFIG_EXTERNAL_INTERFACES
#include <catch2/catch.hpp>
#include <filesystem>
#include <unistd.h>

namespace LaptimerCore::TestHelper::SqliteDatabaseTestHelper
{
std::string getWorkingDir();

std::string getTestDatabseFolder();

std::string getTestDatabseFile(std::string const& dbFile = "trackmanagement_test.db");

} // namespace LaptimerCore::TestHelper::SqliteDatabaseTestHelper

#endif // LAPTIMERCORE_TEST_DUMMY_SQLITEDATABASETESTEVENTLISTENER_HPP

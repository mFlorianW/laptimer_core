#ifndef LAPTIMERCORE_TEST_DUMMY_SQLITEDATABASETESTEVENTLISTENER_HPP
#define LAPTIMERCORE_TEST_DUMMY_SQLITEDATABASETESTEVENTLISTENER_HPP
#define CATCH_CONFIG_EXTERNAL_INTERFACES
#include <catch2/catch.hpp>
#include <filesystem>
#include <unistd.h>

namespace LaptimerCore::Test::Dummy::SqliteDatabaseTestHelper
{
std::string getWorkingDir();

std::string getTestDatabseFolder();

std::string getTestDatabseFile(const std::string &dbFile = "trackmanagement_test.db");

} // namespace LaptimerCore::Test::Dummy::SqliteDatabaseTestHelper

#endif // LAPTIMERCORE_TEST_DUMMY_SQLITEDATABASETESTEVENTLISTENER_HPP

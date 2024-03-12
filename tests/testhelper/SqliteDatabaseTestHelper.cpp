// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "SqliteDatabaseTestHelper.hpp"

namespace LaptimerCore::TestHelper::SqliteDatabaseTestHelper
{

std::string getWorkingDir()
{
    auto buffer = std::array<char, 512>{0};
    auto* bufferPtr = getcwd(&buffer.at(0), buffer.size());
    if (bufferPtr == nullptr) {
        FAIL("Unable to get the database folder.");
    }

    return std::string{&buffer.at(0)};
}

std::string getTestDatabseFolder()
{
    return getWorkingDir() + "/database";
}

std::string getTestDatabseFile(std::string const& dbFile)
{
    return getTestDatabseFolder() + "/" + dbFile;
}

} // namespace LaptimerCore::TestHelper::SqliteDatabaseTestHelper

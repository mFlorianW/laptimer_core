// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "AsyncResultDb.hpp"

namespace Rapid::Storage
{

AsyncResultDb::~AsyncResultDb() = default;
AsyncResultDb::AsyncResultDb(AsyncResultDb&& other) noexcept = default;
AsyncResultDb& AsyncResultDb::operator=(AsyncResultDb&& other) noexcept = default;

void AsyncResultDb::setDbResult(System::Result result, std::string const& errMsg) noexcept
{
    System::AsyncResult::setResult(result, errMsg);
}

} // namespace Rapid::Storage

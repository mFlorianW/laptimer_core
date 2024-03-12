// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "IRestRequestHandler.hpp"
#include "ISessionDatabase.hpp"

namespace LaptimerCore::Rest
{

class SessionEndpoint : public IRestRequestHandler
{
public:
    SessionEndpoint(Storage::ISessionDatabase& database) noexcept;

    RequestHandleResult handleRestRequest(RestRequest& request) noexcept override;

private:
    RequestHandleResult handleGetRequest(RestRequest& request) noexcept;
    RequestHandleResult handleDeleteRequest(RestRequest& request) noexcept;

private:
    Storage::ISessionDatabase& mDb;
};

} // namespace LaptimerCore::Rest

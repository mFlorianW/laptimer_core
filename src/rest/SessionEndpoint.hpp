#pragma once

#include "IRestRequestHandler.hpp"
#include "ISessionDatabase.hpp"

namespace LaptimerCore::Rest
{

class SessionEndpoint : public IRestRequestHandler
{
public:
    SessionEndpoint(Storage::ISessionDatabase &database) noexcept;

    RequestHandleResult handleRestRequest(RestRequest &request) noexcept override;

private:
    Storage::ISessionDatabase &mDb;
};

} // namespace LaptimerCore::Rest

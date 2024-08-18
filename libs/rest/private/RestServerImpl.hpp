// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "IRestServer.hpp"
#include <EventHandler.hpp>
#include <boost/beast.hpp>
#include <thread>
#include <unordered_map>

namespace LaptimerCore::Rest::Private
{
class BoostServer;
class RestServerImpl : public Rest::IRestServer, public System::EventHandler
{
public:
    RestServerImpl();
    /**
     * Default destructor
     */
    ~RestServerImpl() override;

    /**
     * Deleted copy constructor.
     */
    RestServerImpl(RestServerImpl const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    RestServerImpl& operator=(RestServerImpl const& other) = delete;

    /**
     * Deleted move constructor
     */
    RestServerImpl(RestServerImpl&& other) = delete;

    /**
     * Deleted move assignment operator
     */
    RestServerImpl& operator=(RestServerImpl const&& other) = delete;

    /**
     * @copydoc RestServerImpl::start
     */
    [[nodiscard]] ServerStartResult start() noexcept override;

    /**
     * @copydoc RestServerImpl::stop
     */
    void stop() noexcept override;

    /**
     * @copydoc RestServerImpl::registerPostHandler
     */
    void registerPostHandler(std::string const& root, IRestRequestHandler* handler) noexcept override;

    /**
     * copydoc RestServerImpl::registerGetHandler
     */
    void registerGetHandler(std::string const& root, IRestRequestHandler* handler) noexcept override;

    /**
     * @copydoc LaptimerCore::System::EventHandler
     */
    bool handleEvent(System::Event* event) noexcept override;

private:
    RequestHandleResult handleGetRequest(RestRequest& request) noexcept;

    std::thread mServerThread;
    BoostServer* mBoostServer = nullptr;
    std::unordered_map<std::string, IRestRequestHandler*> mGetHandlers;
};

} // namespace LaptimerCore::Rest::Private

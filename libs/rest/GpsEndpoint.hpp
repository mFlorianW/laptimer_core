// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "IPositionDateTimeProvider.hpp"
#include "IRestRequestHandler.hpp"

namespace LaptimerCore::Rest
{

class GpsEndpoint final : public IRestRequestHandler, public Positioning::IPositionDateTimeProvider
{
public:
    /**
     * Creates an Instance of the GpsEndpoint
     */
    GpsEndpoint();

    /**
     * Defalut destructor
     */
    ~GpsEndpoint() override;

    /**
     * Deleted copy constructor.
     */
    GpsEndpoint(GpsEndpoint const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    GpsEndpoint& operator=(GpsEndpoint const& other) = delete;

    /**
     * Deleted move constructor
     */
    GpsEndpoint(GpsEndpoint&& other) = delete;

    /**
     * Deleted move assignment operator
     */
    GpsEndpoint& operator=(GpsEndpoint const&& other) = delete;

    /**
     * @copydoc IRestRequestHandler::handleRestRequest(const RestRequest &request)
     */
    RequestHandleResult handleRestRequest(RestRequest& request) noexcept override;
};
} // namespace LaptimerCore::Rest

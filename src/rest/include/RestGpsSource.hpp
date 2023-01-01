#pragma once

#include "IPositionDateTimeProvider.hpp"
#include "IRestRequestHandler.hpp"

namespace LaptimerCore::Rest
{

class RestGpsSource final : public IRestRequestHandler, public Positioning::IPositionDateTimeProvider
{
public:
    /**
     * Creates an Instance of the RestGpsSource
     */
    RestGpsSource();

    /**
     * Defalut destructor
     */
    ~RestGpsSource() override;

    /**
     * Deleted copy constructor.
     */
    RestGpsSource(const RestGpsSource &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    RestGpsSource &operator=(const RestGpsSource &other) = delete;

    /**
     * Deleted move constructor
     */
    RestGpsSource(RestGpsSource &&other) = delete;

    /**
     * Deleted move assignment operator
     */
    RestGpsSource &operator=(const RestGpsSource &&other) = delete;

    /**
     * @copydoc IRestRequestHandler::handleRestRequest(const RestRequest &request)
     */
    RequestHandleResult handleRestRequest(const RestRequest &request) override;
};
} // namespace LaptimerCore::Rest

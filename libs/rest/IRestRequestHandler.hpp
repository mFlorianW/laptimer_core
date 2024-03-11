#pragma once

#include "RestRequest.hpp"
namespace LaptimerCore::Rest
{

enum class RequestHandleResult
{
    Ok,
    Error
};

class IRestRequestHandler
{
public:
    /**
     * Defalut destructor
     */
    virtual ~IRestRequestHandler() = default;

    /**
     * Deleted copy constructor.
     */
    IRestRequestHandler(IRestRequestHandler const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    IRestRequestHandler& operator=(IRestRequestHandler const& other) = delete;

    /**
     * Deleted move constructor
     */
    IRestRequestHandler(IRestRequestHandler&& other) = delete;

    /**
     * Deleted move assignment operator
     */
    IRestRequestHandler& operator=(IRestRequestHandler const&& other) = delete;

    /**
     * Function that is called when the handler is registered in the RestServer. The reqeust handler shall
     * also set the return body of the request when needed otherwise the return body is empty.
     * @param request The Request that the service receives and that shall be handled.
     * @return RequestHandleResult::Ok The Request is correctly handled.
     * @return RequestHandleResult::Error The Request couldn't be handled.
     */
    virtual RequestHandleResult handleRestRequest(RestRequest& request) noexcept = 0;

protected:
    IRestRequestHandler() = default;
};

} // namespace LaptimerCore::Rest

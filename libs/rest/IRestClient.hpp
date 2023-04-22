#pragma once

#include "RestCall.hpp"
#include "RestRequest.hpp"
#include <string>

namespace LaptimerCore::Rest
{

/**
 * Interface for rest clients then can set send rest request to a server.
 */
class IRestClient
{
public:
    /**
     * Default destructor
     */
    virtual ~IRestClient() noexcept = default;

    /**
     * Deleted copy constructor
     */
    IRestClient(const IRestClient &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    IRestClient &operator=(const IRestClient &other) = delete;

    /**
     * Deleted move operator
     */
    IRestClient(IRestClient &&other) = delete;

    /**
     * Deleted move assignment operator
     */
    IRestClient &operator=(IRestClient &&other) = delete;

    /**
     * Set the server address.
     * @param address The address of the server.
     */
    virtual void setServerAddress(const std::string &address) noexcept = 0;

    /**
     * Set the port of the server.
     * @param port The port of the server.
     */
    virtual void setServerPort(std::uint16_t port) noexcept = 0;

    /**
     * Executes a rest request to the server.
     * @request The rest request that shall be executed against the server.
     * @return A RestCall to check for the result of the call.
     */
    virtual std::shared_ptr<RestCall> execute(const RestRequest &request) noexcept = 0;

protected:
    /**
     * Default destructor
     */
    IRestClient() noexcept = default;
};

} // namespace LaptimerCore::Rest

#pragma once

#include "Path.hpp"
#include "SharedDataPointer.hpp"
#include <string_view>

namespace LaptimerCore::Rest
{

enum class RequestType
{
    Get,
    Post,
    Delete,
};

struct SharedRestRequest;
class RestRequest
{
public:
    /**
     * Creates an emtpy RestRequest instance
     */
    RestRequest() noexcept;

    /**
     * Creates an instance of the RestRequest.
     * @param requestPath The path of the request
     * @param requestBody The rawdata of the request
     */
    RestRequest(RequestType type, std::string requestPath, std::string requestBody = "") noexcept;

    /**
     * Default destructor.
     */
    ~RestRequest() noexcept;

    /**
     * Copy constructor for RestRequest.
     * @param other The object to copy from.
     */
    RestRequest(const RestRequest &other) noexcept;

    /**
     * Copy assignment operator for RestRequest.
     * @param other The object to copy from.
     * @return RestRequest& A reference to the copied instance.
     */
    RestRequest &operator=(const RestRequest &other) noexcept;

    /**
     * The move constructor for RestRequest.
     * @param other The object to move from.
     */
    RestRequest(RestRequest &&other) noexcept;

    /**
     * The move assignment operator for RestRequest.
     * @param other The object to move from.
     * @return RestRequest& A reference of the moved instance.
     */
    RestRequest &operator=(RestRequest &&other) noexcept;

    /**
     * Gives the type of the request.
     * @return The type of the request.
     */
    RequestType getType() const noexcept;

    /**
     * Gives the body of the request for further processing.
     * @return The raw data.
     */
    [[nodiscard]] std::string_view getRequestBody() const noexcept;

    /**
     * Get the path of the Request. Every call should have a path
     * at least one element the path to the endpoint.
     * @reutrn The path
     */
    [[nodiscard]] Path getPath() const noexcept;

    /**
     * Gives the return body for the request that shall be send back to the caller.
     * The body can be empty when the call doesn't need one.
     * @return The return body for the caller.
     */
    std::string_view getReturnBody() const noexcept;

    /**
     * Sets the return body for the call. This setter is typically called by the
     * request handler.
     * @param returnBody The return body for the caller.
     */
    void setReturnBody(const std::string &returnBody) noexcept;

    /**
     * Equal operator
     * @return true The two objects are the same.
     * @return false The two objects are not the same.
     */
    friend bool operator==(const RestRequest &lhs, const RestRequest &rhs) noexcept;

    /**
     * Not Equal operator
     * @return true The two objects are not the same.
     * @return false The two objects are the same.
     */
    friend bool operator!=(const RestRequest &lhs, const RestRequest &rhs) noexcept;

private:
    Common::SharedDataPointer<SharedRestRequest> mData;
};
} // namespace LaptimerCore::Rest

#pragma once

#include "Path.hpp"
#include "SharedDataPointer.hpp"
#include <string_view>

namespace LaptimerCore::Rest
{
struct SharedRestRequest;
class RestRequest
{
public:
    /**
     * Creates an instance of the RestRequest.
     * @param rawData The rawdata of the request
     */
    RestRequest() noexcept;

    /**
     * Default destructor.
     */
    ~RestRequest() noexcept;

    /**
     * Copy constructor for RestRequest.
     * @param other The object to copy from.
     */
    RestRequest(const RestRequest &other) noexcept = default;

    /**
     * Copy assignment operator for RestRequest.
     * @param other The object to copy from.
     * @return RestRequest& A reference to the copied instance.
     */
    RestRequest &operator=(const RestRequest &other) noexcept = default;

    /**
     * The move constructor for RestRequest.
     * @param other The object to move from.
     */
    RestRequest(RestRequest &&other) noexcept = default;

    /**
     * The move assignment operator for RestRequest.
     * @param other The object to move from.
     * @return RestRequest& A reference of the moved instance.
     */
    RestRequest &operator=(RestRequest &&other) noexcept = default;

    /**
     * Gives the body of the request for further processing.
     * @return The raw data.
     */
    [[nodiscard]] std::string_view getRequestBody() const noexcept;

    /**
     * Sets the request body.
     * @param requestBody The new request body
     */
    void setRequestBody(const std::string &requestBody) noexcept;

    /**
     * Get the path of the Request. Every call should have a path
     * at least one element the path to the endpoint.
     * @reutrn The path
     */
    [[nodiscard]] Path getPath() const noexcept;

    /**
     * Sets the raw path and creates internally new instance of Path
     * for further processing. Call @ref RestRequest::getPath() to get
     * the path instance.
     * @param path The raw path.
     */
    void setPath(const std::string &path) noexcept;

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

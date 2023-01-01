#pragma once

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
    RestRequest(const std::string &rawData) noexcept;

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
     * Gives the raw data of the request for further processing.
     * @return The raw data.
     */
    [[nodiscard]] std::string_view getRawData() const noexcept;

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

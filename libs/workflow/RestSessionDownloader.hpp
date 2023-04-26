#pragma once
#include "ISessionDownloader.hpp"

namespace LaptimerCore::Workflow
{
class RestSessionDownloader final : public ISessionDownloader
{
public:
    RestSessionDownloader() noexcept;

    /**
     * Default empty destructor
     */
    ~RestSessionDownloader() noexcept override = default;

    /**
     * Deleted copy constructor
     */
    RestSessionDownloader(const RestSessionDownloader &) = delete;

    /**
     * Deleted copy operator
     */
    RestSessionDownloader &operator=(const RestSessionDownloader &) = delete;

    /**
     * Deleted move constructor
     */
    RestSessionDownloader(RestSessionDownloader &&) = delete;

    /**
     * Deleted move operator
     */
    RestSessionDownloader &operator=(RestSessionDownloader &&) = delete;

    /**
     * @copydoc ISessionDownloader::getSession()
     */
    std::size_t getSessionCount() const noexcept override;

    /**
     * @copydoc ISessionDownloader::featchSessionCount()
     */
    void fetchSessionCount() noexcept override;

    /**
     * @copydoc ISessionDownloader::getSession()
     */
    std::optional<Common::SessionData> getSession(std::size_t index) const noexcept override;

    /**
     * @copydoc ISessionDownloader::downloadSession()
     */
    void downloadSession(std::size_t index) noexcept override;

private:
};

} // namespace LaptimerCore::Workflow

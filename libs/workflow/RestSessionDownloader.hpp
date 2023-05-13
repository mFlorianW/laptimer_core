#pragma once
#include "IRestClient.hpp"
#include "ISessionDownloader.hpp"

namespace LaptimerCore::Workflow
{
class RestSessionDownloader final : public ISessionDownloader
{
public:
    RestSessionDownloader(Rest::IRestClient &restClient) noexcept;

    /**
     * Default empty destructor
     */
    ~RestSessionDownloader() noexcept override = default;

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
    void fetchSessionCountFinished(Rest::RestCall *call) noexcept;

private:
    Rest::IRestClient &mRestClient;
    std::size_t mSessionCount{0};
    std::unordered_map<Rest::RestCall *, std::shared_ptr<Rest::RestCall>> mFetchCounterCache;
};

} // namespace LaptimerCore::Workflow

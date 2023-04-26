#include "RestSessionDownloader.hpp"

namespace LaptimerCore::Workflow
{

RestSessionDownloader::RestSessionDownloader() noexcept
    : ISessionDownloader()
{
}

std::size_t RestSessionDownloader::getSessionCount() const noexcept
{
    return 0;
}

void RestSessionDownloader::fetchSessionCount() noexcept
{
}

std::optional<Common::SessionData> RestSessionDownloader::getSession(std::size_t index) const noexcept
{
    return std::nullopt;
}

void RestSessionDownloader::downloadSession(std::size_t index) noexcept
{
}

} // namespace LaptimerCore::Workflow

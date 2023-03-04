#include "RequestBuilder.hpp"

namespace LaptimerCore::SessionDl
{

RequestBuilder::RequestBuilder(QUrl url) noexcept
    : mUrl{std::move(url)}
{
}

QNetworkRequest RequestBuilder::createSessionCountRequest() const noexcept
{
    auto request = QNetworkRequest{};
    request.setUrl(mUrl.toString().append("/session"));
    return request;
}

QNetworkRequest RequestBuilder::createSessionRequest(std::size_t sessionId) const noexcept
{
    auto request = QNetworkRequest{};
    const auto url = mUrl.toString().append("/session/%1").arg(QString::number(sessionId));
    request.setUrl(url);
    return request;
}

} // namespace LaptimerCore::SessionDl

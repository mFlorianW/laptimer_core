#pragma once

#include <QNetworkRequest>

namespace LaptimerCore::SessionDl
{

class RequestBuilder
{
public:
    RequestBuilder(QUrl url) noexcept;

    QNetworkRequest createSessionCountRequest() const noexcept;

    QNetworkRequest createSessionRequest(std::size_t sessionId) const noexcept;

private:
    QUrl mUrl;
};

} // namespace LaptimerCore::SessionDl

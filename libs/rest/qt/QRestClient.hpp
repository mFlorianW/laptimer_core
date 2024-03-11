#pragma once

#include "IRestClient.hpp"
#include <QtGlobal>

namespace LaptimerCore::Rest
{

struct QRestClientPrivate;
class QRestClient : public IRestClient
{
    Q_DISABLE_COPY_MOVE(QRestClient)
public:
    QRestClient();

    ~QRestClient() noexcept override;

    void setServerAddress(std::string const& url) noexcept override;

    void setServerPort(std::uint16_t port) noexcept override;

    std::shared_ptr<RestCall> execute(RestRequest const& request) noexcept override;

private:
    std::unique_ptr<QRestClientPrivate> d;
};

} // namespace LaptimerCore::Rest

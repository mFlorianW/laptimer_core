#pragma once

#include <QObject>
#include <QString>
#include <QtGlobal>
#include <memory>

namespace LaptimerCore::Common
{
class PositionDateTimeData;
}

struct RestHttpClientPrivate;
class RestHttpClient final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RestHttpClient)
public:
    RestHttpClient();
    ~RestHttpClient() override;

    void setUrl(const QString &url);
    void sendPosition(const LaptimerCore::Common::PositionDateTimeData &position);

private:
    std::unique_ptr<RestHttpClientPrivate> d;
};
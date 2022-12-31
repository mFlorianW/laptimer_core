#include "MainWindowViewModel.hpp"
#include "PositionListModel.hpp"
#include "RestHttpClient.hpp"
#include <ConstantVelocityPositionDateTimeProvider.hpp>
#include <CsvGpsFileReader.hpp>
#include <QDebug>
#include <QUrl>

struct MainWindowViewModelPrivate
{
    PositionListModel mPositionListModel;
    LaptimerCore::Positioning::ConstantVelocityPositionDateTimeProvider mGpsProvider;
    QGeoCoordinate mCurrentPosition;
    bool mGpsSourceActive{false};
    QString mHostAddress{"localhost"};
    QString mHostPort{"3000"};
    RestHttpClient mRestHttpClient;
};

MainWindowViewModel::MainWindowViewModel()
    : d{std::make_unique<MainWindowViewModelPrivate>()}
{
    d->mGpsProvider.positionTimeData.valueChanged().connect(&MainWindowViewModel::handlePositionUpdate, this);
    d->mGpsProvider.setVelocityInMeterPerSecond(80.6667);

    updateUrl();
}

MainWindowViewModel::~MainWindowViewModel() = default;

QAbstractItemModel *MainWindowViewModel::getPositionModel() const noexcept
{
    return &d->mPositionListModel;
}

void MainWindowViewModel::startGpsSource()
{
    d->mGpsProvider.start();
    d->mGpsSourceActive = true;
    Q_EMIT gpsSourceActiveChanged();
}

void MainWindowViewModel::stopGpsSource()
{
    d->mGpsProvider.stop();
    d->mPositionListModel.clear();
    d->mGpsSourceActive = false;
    Q_EMIT gpsSourceActiveChanged();
}

void MainWindowViewModel::loadGpsFile(const QUrl &fileName)
{
    auto csvReader = LaptimerCore::Positioning::Qt::CsvGpsFileReader{};
    csvReader.setFileName(fileName.toLocalFile());
    if (!csvReader.read())
    {
        qCritical() << "Failed to read GpsFile:" << fileName;
    }

    d->mGpsProvider.setGpsPositions(csvReader.getPostions());
}

void MainWindowViewModel::handlePositionUpdate()
{
    const auto position = d->mGpsProvider.positionTimeData.get();
    d->mPositionListModel.addPosition(position);
    d->mCurrentPosition = QGeoCoordinate{position.getPosition().getLatitude(), position.getPosition().getLongitude()};
    d->mRestHttpClient.sendPosition(position);
    Q_EMIT currentPositionChanged();
}

QGeoCoordinate MainWindowViewModel::getCurrentPosition() const noexcept
{
    return d->mCurrentPosition;
}

bool MainWindowViewModel::isGpsSourceActive() const noexcept
{
    return d->mGpsSourceActive;
}

QString MainWindowViewModel::getHostAddress() const noexcept
{
    return d->mHostAddress;
}

void MainWindowViewModel::setHostAddress(const QString &hostAddress)
{
    if (d->mHostAddress != hostAddress)
    {
        d->mHostAddress = hostAddress;
        updateUrl();
        Q_EMIT hostAddressChanged();
    }
}

QString MainWindowViewModel::getHostPort() const noexcept
{
    return d->mHostPort;
}

void MainWindowViewModel::setHostPort(const QString &hostPort)
{
    if (d->mHostPort != hostPort)
    {
        d->mHostPort = hostPort;
        updateUrl();
        Q_EMIT hostPortChanged();
    }
}

void MainWindowViewModel::updateUrl()
{
    const auto newUrl = QString{"http://%1:%2"}.arg(d->mHostAddress, d->mHostPort);
    d->mRestHttpClient.setUrl(newUrl);
}

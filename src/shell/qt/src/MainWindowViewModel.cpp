#include "MainWindowViewModel.hpp"
#include "CsvGpsFileReader.hpp"
#include <ConstantVelocityPositionDateTimeProvider.hpp>
#include <QDebug>
#include <QUrl>

namespace LaptimerCore::QtShel
{

struct MainWindowViewModelPrivate
{
    Positioning::ConstantVelocityPositionDateTimeProvider gpsSource;
    QGeoCoordinate currentPosition;
};

MainWindowViewModel::MainWindowViewModel()
    : QObject{}
    , d{std::make_unique<MainWindowViewModelPrivate>()}
{
    d->gpsSource.positionTimeData.valueChanged().connect(&MainWindowViewModel::handlePositionUpdate, this);
    d->gpsSource.setVelocityInMeterPerSecond(2.77778);
}

MainWindowViewModel::~MainWindowViewModel() = default;

void MainWindowViewModel::startGpsSource()
{
    d->gpsSource.start();
}

void MainWindowViewModel::loadGpsFile(const QUrl &fileName)
{
    auto fileReader = QtShell::CsvGpsFileReader{};
    fileReader.setFileName(fileName.toLocalFile());
    if (!fileReader.read())
    {
        qWarning() << "Failed to read GPS positions of file:" << fileName;
    }

    d->gpsSource.setGpsPositions(fileReader.getPostions());
}

QGeoCoordinate MainWindowViewModel::getCurrentPosition() const noexcept
{
    return d->currentPosition;
}

void MainWindowViewModel::handlePositionUpdate()
{
    auto pos = d->gpsSource.positionTimeData.get();
    d->currentPosition = QGeoCoordinate{pos.getPosition().getLatitude(), pos.getPosition().getLongitude()};

    //    qInfo() << d->currentPosition;

    Q_EMIT currentPositionChanged();
}

} // namespace LaptimerCore::QtShel

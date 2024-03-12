// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MainWindowViewModel.hpp"
#include "CsvGpsFileReader.hpp"
#include <ConstantVelocityPositionDateTimeProvider.hpp>
#include <LapData.hpp>
#include <LaptimeModel.hpp>
#include <QDebug>
#include <QUrl>
#include <SimpleLaptimer.hpp>
#include <Utils.hpp>

namespace LaptimerCore::QtShell
{

struct MainWindowViewModelPrivate
{
    Positioning::ConstantVelocityPositionDateTimeProvider gpsSource;
    QGeoCoordinate currentPosition;
    bool gpsSourceIsActive{false};
    Algorithm::SimpleLaptimer laptimer;
    QString currentLaptime{"00:00:00.000"};
    LaptimeModel laptimeModel;
};

MainWindowViewModel::MainWindowViewModel()
    : QObject{}
    , d{std::make_unique<MainWindowViewModelPrivate>()}
{
    d->gpsSource.positionTimeData.valueChanged().connect(&MainWindowViewModel::handlePositionUpdate, this);
    d->gpsSource.setVelocityInMeterPerSecond(80.6667);

    auto oschersleben = Common::TrackData{};
    oschersleben.setTrackName("Oschersleben");
    oschersleben.setStartline(Common::PositionData{52.0270889, 11.2803483});
    oschersleben.setFinishline(Common::PositionData{52.0270889, 11.2803483});
    oschersleben.setSections(
        {Common::PositionData{52.0298205, 11.2741851}, Common::PositionData{52.0299681, 11.2772076}});

    d->laptimer.setTrack(oschersleben);
    d->laptimer.currentLaptime.valueChanged().connect(&MainWindowViewModel::handleLaptimeChanged, this);
    d->laptimer.lapFinished.connect(&MainWindowViewModel::handleLapFinished, this);
}

MainWindowViewModel::~MainWindowViewModel() = default;

void MainWindowViewModel::startGpsSource()
{
    d->gpsSource.start();
    d->gpsSourceIsActive = true;
    Q_EMIT gpsSourceActiveChanged();
}

void MainWindowViewModel::stopGpsSource()
{
    d->gpsSource.stop();
    d->gpsSourceIsActive = false;
    Q_EMIT gpsSourceActiveChanged();
}

void MainWindowViewModel::loadGpsFile(QUrl const& fileName)
{
    auto fileReader = LaptimerCore::Positioning::Qt::CsvGpsFileReader{};
    fileReader.setFileName(fileName.toLocalFile());
    if (!fileReader.read()) {
        qWarning() << "Failed to read GPS positions of file:" << fileName;
    }

    d->gpsSource.setGpsPositions(fileReader.getPostions());
}

QGeoCoordinate MainWindowViewModel::getCurrentPosition() const noexcept
{
    return d->currentPosition;
}

bool MainWindowViewModel::isGpsSourceActive()
{
    return d->gpsSourceIsActive;
}

QString MainWindowViewModel::getCurrentLaptime() const noexcept
{
    return d->currentLaptime;
}

QAbstractItemModel* MainWindowViewModel::getLaptimeModel() const noexcept
{
    return &d->laptimeModel;
}

void MainWindowViewModel::handlePositionUpdate()
{
    auto pos = d->gpsSource.positionTimeData.get();
    d->currentPosition = QGeoCoordinate{pos.getPosition().getLatitude(), pos.getPosition().getLongitude()};
    d->laptimer.updatePositionAndTime(pos);
    Q_EMIT currentPositionChanged();
}

void MainWindowViewModel::handleLaptimeChanged()
{
    auto laptime = d->laptimer.currentLaptime.get();
    d->currentLaptime = Utils::convertLaptimeToString(laptime);
    Q_EMIT currentLaptimeChanged();
}

void MainWindowViewModel::handleLapFinished()
{
    d->laptimeModel.addLap(Common::LapData{d->laptimer.getLastLaptime()});
}

} // namespace LaptimerCore::QtShell

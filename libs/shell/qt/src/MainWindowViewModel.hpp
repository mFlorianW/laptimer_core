// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef MAINWINDOWVIEWMODEL_HPP
#define MAINWINDOWVIEWMODEL_HPP

#include <QAbstractItemModel>
#include <QGeoCoordinate>
#include <QObject>
#include <memory>

namespace LaptimerCore::QtShell
{

struct MainWindowViewModelPrivate;
class MainWindowViewModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindowViewModel)

    Q_PROPERTY(QGeoCoordinate currentPosition READ getCurrentPosition NOTIFY currentPositionChanged)
    Q_PROPERTY(bool gpsSourceActive READ isGpsSourceActive NOTIFY gpsSourceActiveChanged)
    Q_PROPERTY(QString currentLaptime READ getCurrentLaptime NOTIFY currentLaptimeChanged)
    Q_PROPERTY(QAbstractItemModel* laptimeModel READ getLaptimeModel NOTIFY laptimeModelChanged)
public:
    MainWindowViewModel();

    ~MainWindowViewModel();

    Q_INVOKABLE void startGpsSource();

    Q_INVOKABLE void stopGpsSource();

    Q_INVOKABLE void loadGpsFile(QUrl const& fileName);

    QGeoCoordinate getCurrentPosition() const noexcept;

    bool isGpsSourceActive();

    QString getCurrentLaptime() const noexcept;

    QAbstractItemModel* getLaptimeModel() const noexcept;

Q_SIGNALS:
    void currentPositionChanged();
    void gpsSourceActiveChanged();
    void currentLaptimeChanged();
    void laptimeModelChanged();

private Q_SLOTS:
    void handlePositionUpdate();
    void handleLaptimeChanged();
    void handleLapFinished();

private:
    std::unique_ptr<MainWindowViewModelPrivate> d;
};

} // namespace LaptimerCore::QtShell

#endif // MAINWINDOWVIEWMODEL_HPP

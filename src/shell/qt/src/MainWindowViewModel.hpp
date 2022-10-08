#ifndef MAINWINDOWVIEWMODEL_HPP
#define MAINWINDOWVIEWMODEL_HPP

#include <QGeoCoordinate>
#include <QObject>
#include <memory>

namespace LaptimerCore::QtShel
{

struct MainWindowViewModelPrivate;
class MainWindowViewModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(MainWindowViewModel)

    Q_PROPERTY(QGeoCoordinate currentPosition READ getCurrentPosition NOTIFY currentPositionChanged)
    Q_PROPERTY(bool gpsSourceActive READ isGpsSourceActive NOTIFY gpsSourceActiveChanged)
public:
    MainWindowViewModel();

    ~MainWindowViewModel();

    Q_INVOKABLE void startGpsSource();

    Q_INVOKABLE void stopGpsSource();

    Q_INVOKABLE void loadGpsFile(const QUrl &fileName);

    QGeoCoordinate getCurrentPosition() const noexcept;

    bool isGpsSourceActive();

Q_SIGNALS:
    void currentPositionChanged();
    void gpsSourceActiveChanged();

private Q_SLOTS:
    void handlePositionUpdate();

private:
    std::unique_ptr<MainWindowViewModelPrivate> d;
};

} // namespace LaptimerCore::QtShel

#endif // MAINWINDOWVIEWMODEL_HPP

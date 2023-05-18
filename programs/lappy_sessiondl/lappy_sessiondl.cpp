#include "CliOptions.hpp"
#include "LappySessionDownloader.hpp"
#include <QApplication>
#include <QTimer>
#include <SignalDispatcher.hpp>

int main(int argc, char **argv)
{
    QApplication app{argc, argv};
    app.setApplicationName("lappy");
    app.setOrganizationName("Lappy");
    app.setOrganizationDomain("de.lappy");

    const auto options = LaptimerCore::SessionDl::CliOptions{argc, argv};

    // LaptimerCore::SessionDl::CliOptions opts{argc, argv};
    const auto sDl = LaptimerCore::SessionDl::LappySessionDownloader{options.getHostAddress(), options.getPort()};
    sDl.show();

    auto lappyCoreSignalDispatcher = LaptimerCore::System::SignalDispatcher{};
    auto lappyCoreSignaldispatcherTimer = QTimer{};
    lappyCoreSignaldispatcherTimer.setInterval(std::chrono::milliseconds(1));
    QObject::connect(&lappyCoreSignaldispatcherTimer, &QTimer::timeout, &lappyCoreSignaldispatcherTimer, [&] {
        lappyCoreSignalDispatcher.exec();
    });
    lappyCoreSignaldispatcherTimer.start();

    return app.exec();
}

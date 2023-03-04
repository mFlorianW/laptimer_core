#include "SessionDl.hpp"
#include <QQmlContext>
#include <QQuickWindow>

namespace LaptimerCore::SessionDl
{

SessionDl::SessionDl(QHostAddress const &address, quint16 port) noexcept
{
    auto qmlContext = mEngine.rootContext();
    qmlContext->setContextProperty("g_MainWindowModel", &mMainWindowModel);
    mEngine.load(QUrl{"qrc:/qml/MainWindow.qml"});

    mMainWindowModel.setHostAddress(address);
    mMainWindowModel.setHostPort(port);
}

void SessionDl::show() const noexcept
{
    auto *topLevel = mEngine.rootObjects().value(0);
    auto *window = qobject_cast<QQuickWindow *>(topLevel);
    window->show();
}

} // namespace LaptimerCore::SessionDl

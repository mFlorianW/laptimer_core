#include "LappyShell.hpp"
#include <QQmlContext>
#include <QQuickWindow>

namespace LaptimerCore::LappyShell
{
LappyShell::LappyShell()
{
    // auto qmlContext = mEngine.rootContext();
    // qmlContext->setContextProperty("g_MainWindowModel", &mMainWindowModel);
    mEngine.load(QUrl{"qrc:/qml/MainWindow.qml"});
}

void LappyShell::show() const noexcept
{
    auto *topLevel = mEngine.rootObjects().value(0);
    auto *window = qobject_cast<QQuickWindow *>(topLevel);
    window->show();
}

} // namespace LaptimerCore::LappyShell

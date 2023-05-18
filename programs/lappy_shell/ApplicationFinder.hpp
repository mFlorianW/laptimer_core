#pragma once
#include <QFileInfo>
#include <QStringList>

namespace LaptimerCore::LappyShell
{
class ApplicationFinder
{
public:
    ApplicationFinder(QStringList appDirs);

    QVector<QFileInfo> findApplications() const noexcept;

private:
    QStringList mAppDirs;
};
} // namespace LaptimerCore::LappyShell

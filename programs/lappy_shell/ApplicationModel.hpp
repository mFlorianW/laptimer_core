#pragma once
#include "ApplicationConfig.hpp"
#include <QStringList>
#include <QVector>

namespace LaptimerCore::LappyShell
{
class ApplicationModel
{
public:
    ApplicationModel(QStringList applicationFolders = {}) noexcept;
    void loadApplications() noexcept;
    [[nodiscard]] QVector<ApplicationConfig> getApplications() const noexcept;

private:
    QVector<ApplicationConfig> mApps;
    QStringList mAppFolders;
};

} // namespace LaptimerCore::LappyShell

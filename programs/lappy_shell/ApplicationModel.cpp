// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ApplicationModel.hpp"
#include "ApplicationConfigReader.hpp"
#include "ApplicationFinder.hpp"
#include <QDebug>

namespace LaptimerCore::LappyShell
{
ApplicationModel::ApplicationModel(QStringList applicationFolders) noexcept
    : mAppFolders{std::move(applicationFolders)}
{
}

void ApplicationModel::loadApplications() noexcept
{
    auto finder = ApplicationFinder{mAppFolders};
    auto configFiles = finder.findApplications();
    auto configReader = ApplicationConfigReader{};
    for (auto const& configFile : std::as_const(configFiles)) {
        auto app = configReader.readConfig(configFile.absoluteFilePath());
        if (app) {
            qInfo() << "Found application config in " << configFile.absoluteFilePath();
            mApps.append(app.value());
        } else {
            qInfo() << "Critical failed to load application config:" << configFile.absoluteFilePath();
        }
    }

    std::sort(mApps.begin(), mApps.end(), [](ApplicationConfig const& a, ApplicationConfig const& b) {
        return a.getName() < b.getName();
    });
}

QVector<ApplicationConfig> ApplicationModel::getApplications() const noexcept
{
    return mApps;
}

} // namespace LaptimerCore::LappyShell

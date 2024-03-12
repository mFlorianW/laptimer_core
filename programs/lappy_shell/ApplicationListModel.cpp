#include "ApplicationListModel.hpp"

namespace LaptimerCore::LappyShell
{

ApplicationListModel::ApplicationListModel(ApplicationModel &appModel) noexcept
    : QAbstractListModel{}
    , mAppModel{appModel}
{
}

qint32 ApplicationListModel::rowCount(const QModelIndex &parent) const noexcept
{
    return mAppModel.getApplications().size();
}

QVariant ApplicationListModel::data(const QModelIndex &index, qint32 displayRole) const noexcept
{
    const auto apps = mAppModel.getApplications();
    if (!index.isValid() or index.row() > apps.size())
    {
        return {};
    }

    if (displayRole == DisplayRole::AppName)
    {
        return apps.at(index.row()).getName();
    }
    else if (displayRole == DisplayRole::IconUrl)
    {
        return apps.at(index.row()).getIconUrl();
    }
    return {};
}

QHash<qint32, QByteArray> ApplicationListModel::roleNames() const noexcept
{
    static auto roles = QHash<qint32, QByteArray>{{DisplayRole::AppName, "appName"}, {DisplayRole::IconUrl, "iconUrl"}};
    return roles;
}

} // namespace LaptimerCore::LappyShell

// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DeviceModel.hpp"
#include <QSize>

namespace LaptimerCore::LappyShell::Settings
{

DeviceModel::DeviceModel() = default;
DeviceModel::~DeviceModel() = default;

qint32 DeviceModel::rowCount(QModelIndex const& parent) const
{
    return 0;
}

qint32 DeviceModel::columnCount(QModelIndex const& parent) const
{
    return 4;
}

QVariant DeviceModel::data(QModelIndex const& index, qint32 role) const
{
    return {};
}

QVariant DeviceModel::headerData(qint32 index, Qt::Orientation orientation, qint32 role) const
{
    static std::array<QString, 4> header = {tr("Name"), tr("IP-Address"), tr("Port"), tr("Default")};
    if (role == Qt::DisplayRole and orientation == Qt::Horizontal) {
        if (index >= 0 and index < static_cast<qint32>(header.size())) {
            return header[index];
        }
    }
    return {};
}

} // namespace LaptimerCore::LappyShell::Settings

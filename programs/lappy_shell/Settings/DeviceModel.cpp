// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DeviceModel.hpp"
#include <QSize>

namespace LaptimerCore::LappyShell::Settings
{

DeviceModel::DeviceModel() = default;
DeviceModel::~DeviceModel() = default;

int DeviceModel::rowCount(QModelIndex const& parent) const noexcept
{
    return static_cast<int>(mDevices.size());
}

int DeviceModel::columnCount(QModelIndex const& parent) const noexcept
{
    constexpr auto colums = int{3};
    return colums;
}

QVariant DeviceModel::data(QModelIndex const& index, qint32 role) const noexcept
{
    if (index.row() < 0 or index.row() > mDevices.size()) {
        return {};
    }
    auto const deviceSettings = *(mDevices.cbegin() + index.row());
    auto data = QVariant{};
    if (role == Qt::DisplayRole && index.column() == 0) {
        data = deviceSettings.name;
    } else if (role == Qt::DisplayRole && index.column() == 1) {
        data = deviceSettings.ip.toString();
    } else if (role == Qt::DisplayRole && index.column() == 2) {
        data = QString::number(deviceSettings.port);
    } else if (role == Qt::DisplayRole && index.column() == 3) {
        data = deviceSettings.defaultDevice;
    } else if (role == Qt::TextAlignmentRole) {
        return static_cast<int>(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    return data;
}

QVariant DeviceModel::headerData(qint32 index, Qt::Orientation orientation, qint32 role) const noexcept
{
    static std::array<QString, 4> header = {tr("Name"), tr("IP-Address"), tr("Port"), tr("Default")};
    if (role == Qt::DisplayRole and orientation == Qt::Horizontal) {
        if (index >= 0 and index < static_cast<qint32>(header.size())) {
            return header[index];
        }
    }
    return {};
}

bool DeviceModel::insertRows(int row, int count, QModelIndex const& parent) noexcept
{
    if (row == rowCount({})) {
        beginInsertRows(index(row, 0), row, row + count - 1);
        for (int i = 0; i < count; ++i) {
            mDevices.emplace_back(Common::DeviceSettings{.name = QString{"Lappy"},
                                                         .ip = QHostAddress{QString{"127.0.0.1"}},
                                                         .port = 80,
                                                         .defaultDevice = false});
        }
        endInsertRows();
        return true;
    }
    return false;
}

} // namespace LaptimerCore::LappyShell::Settings

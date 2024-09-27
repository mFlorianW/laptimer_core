// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DeviceModel.hpp"
#include <QSize>

namespace LaptimerCore::LappyShell::Settings
{

namespace
{
constexpr auto columns = int{3};
} // namespace

DeviceModel::DeviceModel() = default;
DeviceModel::~DeviceModel() = default;

int DeviceModel::rowCount(QModelIndex const& parent) const noexcept
{
    return static_cast<int>(mDevices.size());
}

int DeviceModel::columnCount(QModelIndex const& parent) const noexcept
{
    return columns;
}

Qt::ItemFlags DeviceModel::flags(QModelIndex const& index) const noexcept
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QVariant DeviceModel::data(QModelIndex const& index, qint32 role) const noexcept
{
    if (isInvalidIndex(index)) {
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

bool DeviceModel::setData(QModelIndex const& index, QVariant const& value, int role) noexcept
{
    if (isInvalidIndex(index) or role != Qt::EditRole) {
        return {};
    }

    auto device = mDevices.begin() + index.row();
    if (index.column() == 0) {
        device->name = value.toString();
    } else if (index.column() == 1) {
        auto const ip = QHostAddress{value.toString()};
        if (ip.isNull()) {
            return false;
        }
        device->ip = ip;
    } else if (index.column() == 2) {
        auto ok = false;
        auto const port = value.toInt(&ok);
        if (not ok) {
            return false;
        }
        device->port = port;
    }

    qInfo() << "sdfsdfdsfdsfsdfsdfsdf" << device->name;
    Q_EMIT dataChanged(index, index, {Qt::DisplayRole});

    return true;
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

bool DeviceModel::removeRows(int row, int count, QModelIndex const& parent) noexcept
{
    auto lastDevice = mDevices.cbegin() + row + count - 1;
    if (lastDevice != mDevices.cend()) {
        beginRemoveRows({}, row, row + count - 1);
        mDevices.erase(mDevices.begin() + row, mDevices.begin() + row + count);
        endRemoveRows();
        return true;
    }
    return false;
}

bool DeviceModel::isInvalidIndex(QModelIndex const& index) const noexcept
{
    return (index.row() < 0 or index.row() > mDevices.size()) and (index.column() < 0 or index.column() > columns);
}

} // namespace LaptimerCore::LappyShell::Settings

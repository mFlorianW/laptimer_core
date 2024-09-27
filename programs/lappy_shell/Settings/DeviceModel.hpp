// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "GlobalSettingsTypes.hpp"
#include <QAbstractTableModel>

namespace LaptimerCore::LappyShell::Settings
{

/**
 * The device models holds a stored devices
 * Adds new devices and handles the changes of devices.
 */
class DeviceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
     * Creates an instance of @ref DeviceModel.
     */
    DeviceModel();

    /**
     * Default destructor
     */
    ~DeviceModel() override;

    /**
     * Disabled copy and move semantic
     */
    Q_DISABLE_COPY_MOVE(DeviceModel)

    /**
     * Gives the number of devices in the model.
     * @param parent The model index is unused.
     * @return The amount devices in model.
     */
    int rowCount(QModelIndex const& parent) const noexcept override;

    /**
     * Gives the number of column for the view.
     * The model has table has 4 columns:
     * 1. Device Name
     * 2. Device IP-Address
     * 3. Device Port
     * 4. Default Device Option
     * @param paran The parent model index is unused.
     * @return The amout of columns. This is static and is always 4.
     */
    int columnCount(QModelIndex const& parent) const noexcept override;

    /**
     * Gives the data in side model depending of the index and role.
     * @param index The index of the device in the model
     * @param role The role defines which device parameter is returned
     * @return The device data defined by the index and role.
     */
    QVariant data(QModelIndex const& index, qint32 role) const noexcept override;

    /**
     * Gives the titles for the table header.
     * Only the Qt::DisplayRole is supported
     * @param index The table column header index.
     * @param orientation The of the header only Qt::Horizontal is supported.
     * @return The header data for the column.
     */
    QVariant headerData(qint32 index, Qt::Orientation orientation, qint32 role) const noexcept override;

    /**
     * Creates a device setting in the model with default parameters.
     * The function can only append new settings to the model.
     * That means the @param row must be equal to @ref DeviceModel::rowCount.
     * @param row At which row shall the new device settings created.
     * @param count How many device settings shall be created, default 1.
     * @param parent In this case unused.
     * @return true The new devices are created.
     * @return false Failed to create the new devices.
     */
    bool insertRows(int row, int count = 1, QModelIndex const& parent = QModelIndex{}) noexcept override;

private:
    QList<Common::DeviceSettings> mDevices;
};

} // namespace LaptimerCore::LappyShell::Settings

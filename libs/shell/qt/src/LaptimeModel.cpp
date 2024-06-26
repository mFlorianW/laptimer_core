// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "LaptimeModel.hpp"
#include <ILaptimer.hpp>
#include <LapData.hpp>
#include <Utils.hpp>

namespace LaptimerCore::QtShell
{

struct LaptimeModelPrivate
{
    QVector<Common::LapData> laps;
};

LaptimeModel::LaptimeModel()
    : d{std::make_unique<LaptimeModelPrivate>()}
{
}

void LaptimeModel::addLap(Common::LapData const& lap)
{
    beginInsertRows(index(d->laps.size()), d->laps.size(), d->laps.size() + 1);
    d->laps.push_back(lap);
    endResetModel();
}

LaptimeModel::~LaptimeModel() = default;

int LaptimeModel::rowCount(QModelIndex const& parent) const
{
    Q_UNUSED(parent)
    return d->laps.size();
}

QVariant LaptimeModel::data(QModelIndex const& index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    auto lapIter = d->laps.cbegin() + index.row();
    if (role == Roles::laptime) {
        return Utils::convertLaptimeToString(lapIter->getLaptime());
    }
    return {};
}

QHash<int, QByteArray> QtShell::LaptimeModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result.insert(static_cast<qint32>(Roles::laptime), "laptime");

    return result;
}

} // namespace LaptimerCore::QtShell

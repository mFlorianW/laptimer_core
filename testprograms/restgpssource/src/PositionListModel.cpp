#include "PositionListModel.hpp"
#include <PositionDateTimeData.hpp>
#include <QDebug>
#include <memory>

constexpr auto POSITION_BUFFER_SIZE = 300;

class PositionListModelPrivate
{
public:
    std::array<LaptimerCore::Common::PositionDateTimeData, POSITION_BUFFER_SIZE> mPositions{};
    qint32 mWriteIndex{0};
    bool mBufferFull{false};
};

PositionListModel::PositionListModel()
    : QAbstractListModel{}
    , d{std::make_unique<PositionListModelPrivate>()}
{
}

PositionListModel::~PositionListModel() = default;

qint32 PositionListModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return d->mBufferFull ? static_cast<qint32>(d->mPositions.size()) : d->mWriteIndex;
}

QVariant PositionListModel::data(const QModelIndex &index, qint32 role) const
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return {};
    }

    const auto position = d->mPositions.cbegin() + index.row();
    if (role == PositionRole::Latitude)
    {
        return QString::number(position->getPosition().getLatitude());
    }
    else if (role == PositionRole::Longitude)
    {
        return QString::number(position->getPosition().getLongitude());
    }

    return {};
}

QHash<qint32, QByteArray> PositionListModel::roleNames() const
{
    static auto roles =
        QHash<qint32, QByteArray>{{PositionRole::Latitude, "latitude"}, {PositionRole::Longitude, "longitude"}};
    return roles;
}

void PositionListModel::addPosition(const LaptimerCore::Common::PositionDateTimeData &position)
{
    const auto writeIndex = d->mWriteIndex;
    d->mWriteIndex = d->mWriteIndex + 1;
    d->mWriteIndex %= POSITION_BUFFER_SIZE;
    d->mPositions[writeIndex] = position;

    if (!d->mBufferFull)
    {
        beginInsertRows({}, writeIndex, writeIndex);
        endInsertRows();
    }
    else
    {
        Q_EMIT dataChanged(index(writeIndex), index(writeIndex), {PositionRole::Latitude, PositionRole::Longitude});
    }

    // After the first time is buffer is filled we only need to updated the UI.
    if (writeIndex == POSITION_BUFFER_SIZE - 1)
    {
        d->mBufferFull = true;
    }
}

void PositionListModel::clear()
{
    beginResetModel();
    d->mWriteIndex = 0;
    d->mBufferFull = false;
    endResetModel();
}

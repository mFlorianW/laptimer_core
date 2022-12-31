#ifndef POSITIONLISTMODEL_HPP
#define POSITIONLISTMODEL_HPP

#include <QAbstractListModel>
#include <memory>

namespace LaptimerCore::Common
{
class PositionDateTimeData;
}

class PositionListModelPrivate;
class PositionListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(PositionListModel)
public:
    enum PositionRole
    {
        Latitude = Qt::DisplayRole + 1,
        Longitude,
    };
    Q_ENUM(PositionRole)

    PositionListModel();
    ~PositionListModel() override;

    qint32 rowCount(const QModelIndex &index) const override;

    QVariant data(const QModelIndex &index, qint32 role) const override;

    QHash<qint32, QByteArray> roleNames() const override;

    void addPosition(const LaptimerCore::Common::PositionDateTimeData &position);

    void clear();

private:
    std::unique_ptr<PositionListModelPrivate> d;
};

#endif // !POSITIONLISTMODEL_HPP

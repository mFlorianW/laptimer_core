#ifndef LAPTIMEMODEL_HPP
#define LAPTIMEMODEL_HPP

#include <QAbstractListModel>
#include <memory>

namespace LaptimerCore::Algorithm
{
class ILaptimer;
}

namespace LaptimerCore::Common
{
class LapData;
}

namespace LaptimerCore::QtShell
{

struct LaptimeModelPrivate;
class LaptimeModel final : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LaptimeModel)

public:
    enum Roles
    {
        laptime = Qt::UserRole + 1,
    };
    Q_ENUM(Roles)

    LaptimeModel();
    ~LaptimeModel();

    void addLap(const Common::LapData &lap);

    int rowCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    quint32 getSectors() const noexcept;

    QHash<int, QByteArray> roleNames() const override;

private:
    std::unique_ptr<LaptimeModelPrivate> d;
};

} // namespace LaptimerCore::QtShell

#endif // LAPTIMEMODEL_HPP

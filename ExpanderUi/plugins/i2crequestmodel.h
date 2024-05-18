#ifndef I2CREQUESTMODEL_H
#define I2CREQUESTMODEL_H

#include <QAbstractListModel>
#include "plugins/i2crequest.h"


class I2cRequestModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit I2cRequestModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

signals:

private:
    enum ModelRoles {
        TypeRole = Qt::UserRole + 1,
        NameRole,
        RwRole,
        SlaveAddrRole,
        MemAddrRole,
        SizeRole,
        DataRole,
    };
    const QHash<int, QByteArray> role_names_ {
        {TypeRole, "type"},
        {NameRole, "name"},
        {RwRole, "rw"},
        {SlaveAddrRole, "slaveAddr"},
        {MemAddrRole, "memAddr"},
        {SizeRole, "size"},
        {DataRole, "data"},
    };

    QList<I2cRequest> requests_;
};

#endif // I2CREQUESTMODEL_H

#include "i2crequestmodel.h"
#include <QVariant>


I2cRequestModel::I2cRequestModel(QObject *parent)
    : QAbstractListModel{parent}
{
    requests_.clear();
    requests_.append(I2cRequest{I2cReqestType::MasterAction, "MasterAction", 0x42, "write_data", 42});
    requests_.append(I2cRequest{I2cReqestType::SlaveConfig, "SlaveConfig", 0x43, "write_data", 43});
    requests_.append(I2cRequest{I2cReqestType::MasterAction, "MasterAction", 0x44, "write_data", 44});
    requests_.append(I2cRequest{I2cReqestType::SlaveConfig, "SlaveConfig", 0x45, "write_data", 45});
}

int I2cRequestModel::rowCount(const QModelIndex &parent) const
{
    return requests_.size();
}

QHash<int, QByteArray> I2cRequestModel::roleNames() const
{
    return role_names_;
}

QVariant I2cRequestModel::data(const QModelIndex &index, int role) const
{
    const I2cRequest &request = requests_.at(index.row());
    switch (role) {
    case TypeRole:
        return QVariant{"MasterAction"};
    case NameRole:
        return QVariant{request.getName()};
    case RwRole:
        return QVariant{"RW"};
    case SlaveAddrRole:
        return QVariant{request.getSlaveAddr()};
    case MemAddrRole:
        return QVariant{"0x42"};
    case SizeRole:
        return QVariant{42};
    case DataRole:
        return QVariant{"preview"};
    default:
        return QVariant{};
    }
}

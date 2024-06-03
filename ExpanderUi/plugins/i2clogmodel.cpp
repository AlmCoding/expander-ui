#include "i2clogmodel.h"
#include <QVariant>

I2cLogModel::I2cLogModel(QObject* parent) : QAbstractListModel{ parent } {
    logs_.append(I2cLog{ "06d09h43m12s122ms", "I2c1", I2cLogType::MasterAction,  //
                         "Test", "0x042",                                        //
                         "ff ff ff",                                             //
                         "42 33",                                                //
                         3, 2, "OK" });

    logs_.append(I2cLog{ "06d09h43m12s122ms", "I2c2", I2cLogType::MasterAction,  //
                         "Test", "0x042",                                        //
                         "ff ff ff",                                             //
                         "42 33",                                                //
                         3, 2, "OK" });
}

int I2cLogModel::rowCount(const QModelIndex& parent) const { return logs_.size(); }

QHash<int, QByteArray> I2cLogModel::roleNames() const { return role_names_; }

QVariant I2cLogModel::data(const QModelIndex& index, int role) const {
    const I2cLog& log = logs_.at(index.row());

    QString type_name;
    switch (log.getType()) {
        case I2cLogType::MasterAction:
            type_name = "MA";
            break;
        case I2cLogType::SlaveConfig:
            type_name = "SC";
            break;
        case I2cLogType::SlaveNotify:
            type_name = "SN";
            break;
        default:
            type_name = "ERR";
            break;
    }

    switch (role) {
        case TimeRole:
            return QVariant{ log.getTime() };
        case InterfaceRole:
            return QVariant{ log.getInterfaceName() };
        case TypeRole:
            return QVariant{ type_name };
        case NameRole:
            return QVariant{ log.getName() };
        case SlaveAddrRole:
            return QVariant{ log.getSlaveAddr() };
        case WriteDataRole:
            return QVariant{ log.getWriteData() };
        case ReadDataRole:
            return QVariant{ log.getReadData() };
        case WriteSizeRole:
            return QVariant{ log.getWriteSize() };
        case ReadSizeRole:
            return QVariant{ log.getReadSize() };
        case SatusRole:
            return QVariant{ log.getStatus() };
        default:
            return QVariant{};
    }
}

void I2cLogModel::setSelectedLogIdx(int idx) {
    if (idx >= 0 && idx < logs_.size()) {
        selected_log_idx_ = idx;
        emit selectedLogIdxChanged(selected_log_idx_);
    }
}

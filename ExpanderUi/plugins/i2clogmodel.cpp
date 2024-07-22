#include "i2clogmodel.h"
#include <QDateTime>
#include <QVariant>
#include "magic_enum.hpp"
#include "plugins/containers/i2ctypes.h"

I2cLogModel::I2cLogModel(QObject* parent) : QAbstractListModel{ parent } { qDebug() << "I2cLogModel object: " << this; }

int I2cLogModel::rowCount(const QModelIndex& parent) const { return logs_.size(); }

QHash<int, QByteArray> I2cLogModel::roleNames() const { return role_names_; }

QVariant I2cLogModel::data(const QModelIndex& index, int role) const {
    const I2cLog& log = logs_.at(index.row());

    QString type_name;
    switch (log.getType()) {
        case I2cTypes::I2cReqestType::MasterAction:
            type_name = "MR";
            break;
        case I2cTypes::I2cReqestType::SlaveConfig:
            type_name = "SC";
            break;
        case I2cTypes::I2cReqestType::SlaveNotify:
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

void I2cLogModel::appendNewLog(const I2cRequest& request) {
    QString interface_name{ magic_enum::enum_name(request.getI2cId()).data() };
    QString status_code{ magic_enum::enum_name(request.getStatus().getStatusCode()).data() };

    I2cLog new_log{ QDateTime::currentDateTime().toString("hh:mm:ss.zzz"),
                    interface_name,
                    request.getType(),
                    request.getName(),
                    request.getSlaveAddr(),
                    request.getWriteData(),
                    request.getStatus().getReadData(),
                    request.getWriteSize(),
                    request.getStatus().getReadSize(),
                    status_code };

    QAbstractItemModel::beginInsertRows(QModelIndex(), logs_.size(), logs_.size());
    logs_.append(new_log);
    QAbstractItemModel::endInsertRows();
}

void I2cLogModel::appendNewLog(const I2cNotification& notification) {}

void I2cLogModel::clearModel() {
    QAbstractItemModel::beginResetModel();
    logs_.clear();
    QAbstractItemModel::endResetModel();
}

#include "i2clogmodel.h"
#include <QDateTime>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include "magic_enum.hpp"
#include "plugins/containers/i2c/i2ctypes.h"
// #include "utility.h"

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
            return QVariant{ truncateNameString(log.getName()) };
        case SlaveAddrRole:
            return QVariant{ log.getSlaveAddr() };
        case WriteDataRole:
            return QVariant{ log.getWriteData() };
        case WriteDataAsciiRole:
            return QVariant{ log.getWriteDataAscii() };
        case ReadDataRole:
            return QVariant{ log.getReadData() };
        case ReadDataAsciiRole:
            return QVariant{ log.getReadDataAscii() };
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

    QString write_data;
    QString write_size;
    QString read_data;
    QString read_size;

    if (status_code == "Success") {
        write_data = request.getWriteData();
        write_size = request.getWriteSize();
        read_data = request.getStatus().getReadData();
        read_size = request.getStatus().getReadSize();

    } else if (status_code == "SlaveNack") {
        write_data = request.getWriteData();
        write_data.insert(request.getStatus().getNackIdx() * 2, "<del>");
        write_data.append("</del>");
        if (request.getStatus().getNackIdx() == 0) {
            write_size = "0/" + request.getWriteSize();
        } else {
            write_size = QString::number(request.getStatus().getNackIdx() - 1) + "/" + request.getWriteSize();
        }

        read_data = request.getStatus().getReadData();
        read_size = request.getStatus().getReadSize() + "/" + request.getReadSize();

    } else if (status_code == "SlaveBusy") {
        write_size = "0/" + request.getWriteSize();
        read_size = "0/" + request.getReadSize();
    }

    I2cLog new_log{ QDateTime::currentDateTime().toString("hh:mm:ss.zzz"),
                    interface_name,
                    request.getType(),
                    request.getName(),
                    request.getSlaveAddr(),
                    write_data,
                    read_data,
                    write_size,
                    read_size,
                    status_code };

    QAbstractItemModel::beginInsertRows(QModelIndex(), logs_.size(), logs_.size());
    logs_.append(new_log);
    QAbstractItemModel::endInsertRows();
}

void I2cLogModel::appendNewLog(const I2cNotification& notification) {
    QString interface_name{ magic_enum::enum_name(notification.getI2cId()).data() };
    QString status_code{ magic_enum::enum_name(notification.getStatusCode()).data() };
    QString notification_name{ "Slave Access #" + QString::number(notification.getAccessId()) };

    I2cLog new_log{ QDateTime::currentDateTime().toString("hh:mm:ss.zzz"),
                    interface_name,
                    I2cTypes::I2cReqestType::SlaveNotify,
                    notification_name,
                    QString{ "" },
                    notification.getWriteData(),
                    notification.getReadData(),
                    notification.getWriteSize(),
                    notification.getReadSize(),
                    status_code };

    QAbstractItemModel::beginInsertRows(QModelIndex(), logs_.size(), logs_.size());
    logs_.append(new_log);
    QAbstractItemModel::endInsertRows();
}

void I2cLogModel::saveLogsToFile(const QString& file_path) {
    QFile file{ file_path };
    if (file.open(QIODevice::WriteOnly) == false) {
        qDebug("Failed to open file for writing!");
        return;
    }

    QJsonArray log_list;
    for (const I2cLog& log : logs_) {
        QJsonObject log_obj;
        log_obj["time"] = log.getTime();
        log_obj["interface"] = log.getInterfaceName();
        log_obj["type"] = static_cast<int>(log.getType());
        log_obj["name"] = log.getName();
        log_obj["slaveAddr"] = log.getSlaveAddr();
        log_obj["writeData"] = log.getWriteData();
        log_obj["readData"] = log.getReadData();
        log_obj["writeSize"] = log.getWriteSize();
        log_obj["readSize"] = log.getReadSize();
        log_obj["status"] = log.getStatus();
        log_list.append(log_obj);
    }

    QJsonObject main_obj;
    main_obj["logs"] = log_list;
    QJsonDocument doc{ main_obj };
    QString json_str{ doc.toJson() };

    QTextStream out{ &file };
    out << json_str;

    file.close();
}

void I2cLogModel::loadLogsFromFile(const QString& file_path) {
    QFile file{ file_path };
    if (file.open(QIODevice::ReadOnly) == false) {
        qDebug("Failed to open file for reading!");
        return;
    }

    QByteArray data{ file.readAll() };
    QJsonDocument doc{ QJsonDocument::fromJson(data) };
    QJsonObject main_obj{ doc.object() };

    QList<I2cLog> logs;
    for (const QJsonValue& log_val : main_obj["logs"].toArray()) {
        QJsonObject log_obj{ log_val.toObject() };

        I2cTypes::I2cReqestType type{ static_cast<I2cTypes::I2cReqestType>(log_obj["type"].toInt()) };
        QString time{ log_obj["time"].toString() };
        QString interface_name{ log_obj["interface"].toString() };
        QString name{ log_obj["name"].toString() };
        QString slave_addr{ log_obj["slaveAddr"].toString() };
        QString write_data{ log_obj["writeData"].toString() };
        QString read_data{ log_obj["readData"].toString() };
        QString write_size{ log_obj["writeSize"].toString() };
        QString read_size{ log_obj["readSize"].toString() };
        QString status{ log_obj["status"].toString() };

        I2cLog log{
            time, interface_name, type, name, slave_addr, write_data, read_data, write_size, read_size, status
        };
        logs.append(log);
    }
    file.close();

    QAbstractItemModel::beginResetModel();
    logs_ = logs;
    QAbstractItemModel::endResetModel();
}

void I2cLogModel::clear() {
    QAbstractItemModel::beginResetModel();
    logs_.clear();
    QAbstractItemModel::endResetModel();
}

QString I2cLogModel::truncateNameString(const QString& str) const {
    QString truncated = font_metrics_.elidedText(str, Qt::ElideRight, LogEntryNameMaxWidth);
    return truncated;
}

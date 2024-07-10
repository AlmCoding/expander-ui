#include "i2crequestmodel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include "plugins/containers/i2ctypes.h"

I2cRequestModel::I2cRequestModel(QObject* parent) : QAbstractListModel{ parent } {}

int I2cRequestModel::rowCount(const QModelIndex& parent) const { return requests_.size(); }

QHash<int, QByteArray> I2cRequestModel::roleNames() const { return role_names_; }

QVariant I2cRequestModel::data(const QModelIndex& index, int role) const {
    const I2cRequest& request = requests_.at(index.row());

    QString type_name{ (request.getType() == I2cTypes::I2cReqestType::MasterAction) ? "MR" : "SC" };

    switch (role) {
        case NameRole:
            return QVariant{ request.getName() };
        case TypeRole:
            return QVariant{ type_name };
        case SlaveAddrRole:
            return QVariant{ request.getSlaveAddr() };
        case WriteDataRole:
            return QVariant{ request.getWriteData() };
        case SizeRole:
            return QVariant{ request.getWriteSize() + "+" + request.getReadSize() };
        default:
            return QVariant{};
    }
}

void I2cRequestModel::addNewRequest(int template_req_idx) {
    I2cRequest request{};
    request.setReadSize("0");

    if (template_req_idx >= 0 && template_req_idx < requests_.size()) {
        request = requests_.at(template_req_idx);
        request.setName(request.getName() + "_copy");
    }

    QAbstractListModel::beginInsertRows(QModelIndex(), requests_.size(), requests_.size());
    requests_.append(request);
    QAbstractListModel::endInsertRows();

    selected_request_idx_ = requests_.size() - 1;
    emit selectedRequestIdxChanged(selected_request_idx_);
}

void I2cRequestModel::deleteRequest(int request_idx) {
    if (request_idx >= 0 && request_idx < requests_.size()) {
        QAbstractListModel::beginRemoveRows(QModelIndex(), request_idx, request_idx);
        requests_.removeAt(request_idx);
        QAbstractListModel::endRemoveRows();
    }

    if (selected_request_idx_ > 0 && selected_request_idx_ >= requests_.size()) {
        selected_request_idx_ = requests_.size() - 1;
        emit selectedRequestIdxChanged(selected_request_idx_);
    }
}

void I2cRequestModel::setSelectedRequestIdx(int idx) {
    if (idx >= 0 && idx < requests_.size()) {
        selected_request_idx_ = idx;
        emit selectedRequestIdxChanged(selected_request_idx_);
    }
}

void I2cRequestModel::updateSelectedRequest(I2cRequest request) {
    if (selected_request_idx_ >= 0 && selected_request_idx_ < requests_.size()) {
        requests_[selected_request_idx_] = request;
        emit QAbstractListModel::dataChanged(index(selected_request_idx_), index(selected_request_idx_));
    }
}

void I2cRequestModel::saveRequestsToFile(const QString& file_path) {
    QFile file{ file_path };
    if (file.open(QIODevice::WriteOnly) == false) {
        qDebug("Failed to open file for writing!");
        return;
    }

    QJsonArray request_list;
    for (const I2cRequest& request : requests_) {
        QJsonObject req_obj;
        req_obj["type"] = static_cast<int>(request.getType());
        req_obj["name"] = request.getName();
        req_obj["slaveAddr"] = request.getSlaveAddr();
        req_obj["writeData"] = request.getWriteData();
        req_obj["readSize"] = request.getReadSize();
        request_list.append(req_obj);
    }

    QJsonObject main_obj;
    main_obj["requests"] = request_list;
    QJsonDocument doc{ main_obj };
    QString json_str{ doc.toJson() };

    QTextStream out{ &file };
    out << json_str;
}

void I2cRequestModel::loadRequestsFromFile(const QString& file_path) {
    QFile file{ file_path };
    if (file.open(QIODevice::ReadOnly) == false) {
        qDebug("Failed to open file for reading!");
        return;
    }

    QByteArray data{ file.readAll() };
    QJsonDocument doc{ QJsonDocument::fromJson(data) };
    QJsonObject main_obj{ doc.object() };

    QList<I2cRequest> requests;
    for (const QJsonValue& req_val : main_obj["requests"].toArray()) {
        QJsonObject req_obj{ req_val.toObject() };

        I2cTypes::I2cReqestType type{ static_cast<I2cTypes::I2cReqestType>(req_obj["type"].toInt()) };
        QString name{ req_obj["name"].toString() };
        QString slave_addr{ req_obj["slaveAddr"].toString() };
        QString write_data{ req_obj["writeData"].toString() };
        QString read_size{ req_obj["readSize"].toString() };

        I2cRequest request{ type, name, slave_addr, write_data, read_size };
        requests.append(request);
    }

    QAbstractItemModel::beginResetModel();
    requests_ = requests;
    QAbstractItemModel::endResetModel();
}

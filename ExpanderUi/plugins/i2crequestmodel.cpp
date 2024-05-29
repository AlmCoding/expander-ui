#include "i2crequestmodel.h"
#include <QVariant>

I2cRequestModel::I2cRequestModel(QObject* parent) : QAbstractListModel{ parent } {}

int I2cRequestModel::rowCount(const QModelIndex& parent) const { return requests_.size(); }

QHash<int, QByteArray> I2cRequestModel::roleNames() const { return role_names_; }

QVariant I2cRequestModel::data(const QModelIndex& index, int role) const {
    const I2cRequest& request = requests_.at(index.row());
    switch (role) {
        case TypeRole:
            return QVariant{ "MasterAction" };
        case NameRole:
            return QVariant{ request.getName() };
        case RwRole:
            return QVariant{ "MR" };
        case SlaveAddrRole:
            return QVariant{ request.getSlaveAddr() };
        case MemAddrRole:
            return QVariant{ request.getWriteData() };
        case SizeRole:
            return QVariant{ request.getWriteSize() + "+" + request.getReadSize() };
        case DataRole:
            return QVariant{ "preview" };
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

    beginInsertRows(QModelIndex(), requests_.size(), requests_.size());
    requests_.append(request);
    endInsertRows();

    selected_request_idx_ = requests_.size() - 1;
    emit selectedRequestIdxChanged(selected_request_idx_);
}

void I2cRequestModel::deleteRequest(int request_idx) {
    if (request_idx >= 0 && request_idx < requests_.size()) {
        beginRemoveRows(QModelIndex(), request_idx, request_idx);
        requests_.removeAt(request_idx);
        endRemoveRows();
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

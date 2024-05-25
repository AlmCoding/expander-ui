#include "i2crequestmodel.h"
#include <QVariant>

I2cRequestModel::I2cRequestModel(QObject* parent) : QAbstractListModel{ parent } {
    requests_.clear();
    // requests_.append(I2cRequest{ I2cReqestType::MasterAction, "MasterAction", 0x42, "write_data", 42 });
    // requests_.append(I2cRequest{ I2cReqestType::SlaveConfig, "SlaveConfig", 0x43, "write_data", 43 });
}

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
            return QVariant{ "RW" };
        case SlaveAddrRole:
            return QVariant{ request.getSlaveAddr() };
        case MemAddrRole:
            return QVariant{ "0x42" };
        case SizeRole:
            return QVariant{ 42 };
        case DataRole:
            return QVariant{ "preview" };
        default:
            return QVariant{};
    }
}

void I2cRequestModel::addNewRequest(int template_req_idx) {
    I2cRequest new_request{};

    if (template_req_idx < requests_.size()) {
        new_request = requests_.at(template_req_idx);
        new_request.setName(new_request.getName() + "_copy");
    }

    beginInsertRows(QModelIndex(), requests_.size(), requests_.size());
    requests_.append(new_request);
    endInsertRows();

    selected_request_idx_ = requests_.size() - 1;
    emit selectedRequestIdxChanged(selected_request_idx_);
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

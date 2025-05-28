#include "i2crequestmodel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include "plugins/containers/i2c/i2ctypes.h"
#include "utility.h"

I2cRequestModel::I2cRequestModel(QObject* parent) : QAbstractListModel{ parent } {}

Qt::ItemFlags I2cRequestModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    if (index.isValid() == true) {
        flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    } else {
        // Not be needed because only elments already in the model can be dragged
        // flags |= Qt::ItemIsDropEnabled;  // Can be dropped into the top level of the model
    }
    return flags;
}

// Qt::DropActions I2cRequestModel::supportedDropActions() const { return Qt::CopyAction | Qt::MoveAction; }

// QStringList I2cRequestModel::mimeTypes() const { return QStringList{ "application/i2crequest" }; }

int I2cRequestModel::rowCount(const QModelIndex& parent) const { return requests_.size(); }

QHash<int, QByteArray> I2cRequestModel::roleNames() const { return role_names_; }

QVariant I2cRequestModel::data(const QModelIndex& index, int role) const {
    const I2cRequest& request = requests_.at(index.row());

    QString type_name{ (request.getType() == I2cTypes::I2cReqestType::MasterAction) ? "MR" : "SC" };

    switch (role) {
        case NameRole:
            return QVariant{ truncateNameString(request.getName()) };
        case TypeRole:
            return QVariant{ type_name };
        case SlaveAddrRole:
            return QVariant{ request.getSlaveAddr() };
        case WriteDataRole:
            // return QVariant{ truncateDataString(request.getWriteData()) };
            return QVariant{ truncateDataString(Utility::convertHexToAscii(request.getWriteData())) };
        case SizeRole:
            return QVariant{ request.getWriteSize() + "+" + request.getReadSize() };
        default:
            return QVariant{};
    }
}

bool I2cRequestModel::moveRows(const QModelIndex& sourceParent, int sourceRow, int count,
                               const QModelIndex& destinationParent, int destinationChild) {
    qDebug() << "Move rows: " << sourceRow << "(" << count << ") ->" << destinationChild;

    // if (sourceParent.isValid() == false || destinationParent.isValid() == false) {
    //   return false;
    // }

    if (sourceRow < 0 || sourceRow >= requests_.size() || destinationChild < 0 || destinationChild > requests_.size()) {
        return false;
    }

    // See https://doc.qt.io/qt-6/qabstractitemmodel.html#beginMoveRows
    int correction = destinationChild > sourceRow ? 1 : 0;
    qDebug() << "beginMoveRows(" << sourceRow << sourceRow + count - 1 << destinationChild + correction << ")";
    if (QAbstractItemModel::beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent,
                                          destinationChild + correction) == false) {
        qDebug() << "Failed to begin move rows!";
        return false;
    }

    QList<I2cRequest> requests;
    for (int i = 0; i < count; i++) {
        requests.append(requests_.takeAt(sourceRow));
    }

    for (int i = 0; i < count; i++) {
        requests_.insert(destinationChild + i, requests.at(i));
    }

    QAbstractItemModel::endMoveRows();

    // Print new order of requests
    qDebug() << "New requests order:";
    for (int i = 0; i < requests_.size(); i++) {
        qDebug() << requests_.at(i).getName();
    }

    return true;
}

/*
bool I2cRequestModel::removeRows(int row, int count, const QModelIndex& parent) {
    if (row < 0 || row >= requests_.size() || count < 1 || row + count > requests_.size()) {
        return false;
    }

 QAbstractItemModel::beginRemoveRows(parent, row, row + count - 1);
 for (int i = 0; i < count; i++) {
     requests_.removeAt(row);
 }
 QAbstractItemModel::endRemoveRows();

 return true;
}

bool I2cRequestModel::insertRows(int row, int count, const QModelIndex& parent) {
 if (row < 0 || row > requests_.size() || count < 1) {
     return false;
 }

 QAbstractItemModel::beginInsertRows(parent, row, row + count - 1);
 for (int i = 0; i < count; i++) {
     requests_.insert(row, I2cRequest{});
 }
 QAbstractItemModel::endInsertRows();

 return true;
}

QMimeData* I2cRequestModel::mimeData(const QModelIndexList& indexes) const {
 QMimeData* mime_data = new QMimeData{};
 QByteArray encoded_data;

 QDataStream stream{ &encoded_data, QIODevice::WriteOnly };
 for (const QModelIndex& index : indexes) {
     if (index.isValid() == true) {
         stream << index.row();
     }
 }

 mime_data->setData("application/i2crequest", encoded_data);
 return mime_data;
}

bool I2cRequestModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                   const QModelIndex& parent) const {
 Q_UNUSED(row);
 Q_UNUSED(column);
 Q_UNUSED(parent);

 if (action == Qt::IgnoreAction) {
     return true;
 } else if (data->hasFormat("application/i2crequest") == false) {
     return false;
 }

 return true;
}

bool I2cRequestModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                const QModelIndex& parent) {
 Q_UNUSED(column);
 Q_UNUSED(parent);

 if (action == Qt::IgnoreAction) {
     return true;
 } else if (data->hasFormat("application/i2crequest") == false) {
     return false;
 }

 QByteArray encoded_data = data->data("application/i2crequest");
 QDataStream stream(&encoded_data, QIODevice::ReadOnly);
 QList<I2cRequest> requests;
 I2cRequest request;

 while (stream.atEnd() == false) {
     stream >> request;  // Deserialize Request object
     requests.append(request);
 }

 QAbstractItemModel::beginInsertRows(parent, row, row + requests.count() - 1);
 // Insert the deserialized requests into your internal list
 for (const I2cRequest& request : requests) {
     requests_.insert(row, request);  // Assuming requests_ is a QList<I2cRequest>
     row++;                           // Increment row for the next insertion
 }
 QAbstractItemModel::endInsertRows();

 return true;
}
*/

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
    }

    // Emit change to update request form with request data who replaces deleted request
    if (requests_.size() > 0) {
        emit selectedRequestIdxChanged(selected_request_idx_);
    }
}

void I2cRequestModel::setSelectedRequestIdx(int idx) {
    if (idx >= 0 && idx < requests_.size()) {
        selected_request_idx_ = idx;
        emit selectedRequestIdxChanged(selected_request_idx_);
    }
}

void I2cRequestModel::setFilePath(QString file_path) {
    file_path_ = file_path;
    emit filePathChanged(file_path_);
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

    file.close();
    setFilePath(file_path);
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
    file.close();
    setFilePath(file_path);

    QAbstractItemModel::beginResetModel();
    requests_ = requests;
    QAbstractItemModel::endResetModel();
}

void I2cRequestModel::clear() {
    QAbstractItemModel::beginResetModel();
    requests_.clear();
    QAbstractItemModel::endResetModel();
}

QString I2cRequestModel::truncateNameString(const QString& str) const {
    QString truncated = font_metrics_.elidedText(str, Qt::ElideRight, RequestNameMaxWidth);
    return truncated;
}

QString I2cRequestModel::truncateDataString(const QString& str) const {
    QString truncated = str.left(RequestDataMaxChars);
    while (font_metrics_.horizontalAdvance(truncated) > RequestDataMaxWidth) {
        int excess_len = truncated.size() % 3;
        if (excess_len == 0) {
            excess_len = 3;
        }
        truncated.chop(excess_len);
    }
    if (truncated.size() < str.size()) {
        truncated.append("...");
    }
    return truncated;
}

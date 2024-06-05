#include "comportmodel.h"

ComPortModel::ComPortModel(QObject* parent) : QAbstractListModel{ parent } {
    updatePorts();
    timer_ = new QTimer{ this };
    connect(timer_, &QTimer::timeout, this, &ComPortModel::updatePorts);
    timer_->start(PortUpdateIntervalMs);
}

int ComPortModel::rowCount(const QModelIndex& parent) const { return ports_.size(); }

QVariant ComPortModel::data(const QModelIndex& index, int role) const {
    if (index.isValid() == false || index.row() >= ports_.size()) {
        return QVariant();
    }

    const QSerialPortInfo& port = ports_.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            return QVariant{ port.portName() };
        case Qt::EditRole:
            return QVariant{ port.portName() };
        default:
            return QVariant{};
    }
}

void ComPortModel::setSelectedPortIdx(int idx) {
    if (update_index_ == true) {
        update_index_ = false;
        return;
    }

    if (idx >= 0 && idx < ports_.size()) {
        selected_port_idx_ = idx;
        emit selectedPortIdxChanged(selected_port_idx_);
    }
}

QSerialPortInfo ComPortModel::getSelectedPort() const {
    if (selected_port_idx_ >= 0 && selected_port_idx_ < ports_.size()) {
        return ports_.at(selected_port_idx_);
    }
    return QSerialPortInfo{};
}

void ComPortModel::updatePorts() {
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    // qDebug() << "Update ports";
    // for (const QSerialPortInfo& portInfo : serialPortInfos) {
    //     qDebug() << "\n"
    //              << "Port:" << portInfo.portName() << "\n"
    //              << "Location:" << portInfo.systemLocation() << "\n"
    //              << "Description:" << portInfo.description() << "\n"
    //              << "Manufacturer:" << portInfo.manufacturer() << "\n"
    //              << "Serial number:" << portInfo.serialNumber() << "\n"
    //              << "Vendor Identifier:"
    //              << (portInfo.hasVendorIdentifier() ? QByteArray::number(portInfo.vendorIdentifier(), 16)
    //                                                 : QByteArray())
    //              << "\n"
    //              << "Product Identifier:"
    //              << (portInfo.hasProductIdentifier() ? QByteArray::number(portInfo.productIdentifier(), 16)
    //                                                  : QByteArray());
    // }

    if (ports_.size() == 0 && serialPortInfos.size() > 0) {
        update_index_ = true;
    }

    beginResetModel();
    ports_ = serialPortInfos;
    endResetModel();

    if (update_index_ == true) {
        selected_port_idx_ = 0;
        emit selectedPortIdxChanged(selected_port_idx_);
    }
    emit portCountChanged(ports_.size());
}

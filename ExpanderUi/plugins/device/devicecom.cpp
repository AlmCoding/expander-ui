#include "devicecom.h"
#include <QDebug>
#include <QSerialPortInfo>

DeviceCom::DeviceCom(QObject* parent) : QObject{ parent } {}

void DeviceCom::run() {
    qDebug() << "Run in DeviceCom thread";

    serial_port_ = new QSerialPort{};

    // exec();
}

void DeviceCom::openPort(const QSerialPortInfo& port_info) {
    qDebug() << "Open port in DeviceCom thread";
    if (serial_port_ == nullptr) {
        serial_port_ = new QSerialPort{};
    }

    serial_port_->setPort(port_info);
    serial_port_->open(QIODevice::ReadWrite);

    if (serial_port_->isOpen()) {
        is_open_ = true;
        emit openStateChanged(true);
    }
}

void DeviceCom::closePort() {
    qDebug() << "Close port in DeviceCom thread";
    if (serial_port_ == nullptr) {
        return;
    }

    serial_port_->close();
    is_open_ = false;
    emit openStateChanged(false);
}

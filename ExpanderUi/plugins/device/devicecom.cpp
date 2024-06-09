#include "devicecom.h"
#include <QDebug>
#include <QSerialPortInfo>
#include "plugins/device/driver/framedriver.h"

DeviceCom::DeviceCom(QObject* parent) : QObject{ parent } {}

DeviceCom::~DeviceCom() {
    if (serial_port_ != nullptr) {
        closePort();
        delete serial_port_;
    }
    if (timer_ != nullptr) {
        timer_->stop();
        delete timer_;
    }
}

void DeviceCom::run() {
    qDebug() << "Run in DeviceCom thread";
    serial_port_ = new QSerialPort{ this };

    connect(serial_port_, &QSerialPort::readyRead, this, [this]() {
        QByteArray data = serial_port_->readAll();
        driver::tf::FrameDriver::getInstance().receiveData(data);
    });

    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::sendData, this,
            [this](const QByteArray& data) { serial_port_->write(data); });

    timer_ = new QTimer{ this };
    connect(timer_, &QTimer::timeout, this, &DeviceCom::triggerEcho);
}

void DeviceCom::openPort(const QSerialPortInfo& port_info) {
    qDebug() << "Open port in DeviceCom thread";
    if (serial_port_ == nullptr || serial_port_->isOpen() == true) {
        return;
    }

    serial_port_->setPort(port_info);
    serial_port_->open(QIODevice::ReadWrite);
    emit openStateChanged(serial_port_->isOpen());

    timer_->start(10);
}

void DeviceCom::closePort() {
    qDebug() << "Close port in DeviceCom thread";
    if (serial_port_ == nullptr || serial_port_->isOpen() == false) {
        return;
    }

    timer_->stop();
    serial_port_->close();
    emit openStateChanged(serial_port_->isOpen());
}

void DeviceCom::triggerEcho() {
    QByteArray data{ "Who is John Galt? Who is Howard Roak?" };

    if (serial_port_ != nullptr && serial_port_->isOpen() == true) {
        driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::EchoMsg, data);
    }
}
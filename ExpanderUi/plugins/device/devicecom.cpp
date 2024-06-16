#include "devicecom.h"
#include <QDebug>
#include <QSerialPortInfo>
#include "plugins/device/driver/framedriver.h"
#include "plugins/device/driver/i2cprotocom.h"

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

void DeviceCom::handleEchoMessage(const QByteArray& data) { qDebug() << "Echo closed: " << data; }

void DeviceCom::handleI2cMessage(const QByteArray& data) { qDebug() << "I2C message received: " << data; }

void DeviceCom::run() {
    qDebug() << "Run in DeviceCom thread";
    serial_port_ = new QSerialPort{ this };

    connect(serial_port_, &QSerialPort::readyRead, this, [this]() {
        QByteArray data = serial_port_->readAll();
        driver::tf::FrameDriver::getInstance().receiveData(data);
    });

    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::sendData, this,
            [this](const QByteArray& data) {
                if (serial_port_ != nullptr && serial_port_->isOpen() == true)
                    serial_port_->write(data);
                else
                    qDebug("Drop frame due to closed port!");
            });

    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::echoMessage, this,
            &DeviceCom::handleEchoMessage);
    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::i2cMessage, this,
            &DeviceCom::handleI2cMessage);

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

    timer_->start(1000);
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

void DeviceCom::sendI2cConfig(I2cConfig config) {
    qDebug() << "sendI2cConfig in DeviceCom thread";

    // Build message
    QByteArray message{ 128, 0 };
    I2cProtoCom::encodeI2cConfig(config, message);

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::I2cMsg, message);
}

void DeviceCom::sendI2cRequest(I2cRequest request) {
    qDebug() << "sendI2cRequest in DeviceCom thread";

    // Build message
    QByteArray message{ 128, 0 };
    I2cProtoCom::encodeI2cRequest(request, message);

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::I2cMsg, message);
}

void DeviceCom::triggerEcho() {
    QByteArray message{ "Who is John Galt? Who is Howard Roak?" };
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::EchoMsg, message);
}

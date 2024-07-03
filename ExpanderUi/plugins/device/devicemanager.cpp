#include "devicemanager.h"
#include <QDebug>
#include <QSerialPortInfo>
#include "plugins/device/driver/framedriver.h"

DeviceManager::DeviceManager(QObject* parent) : QObject{ parent } {}

DeviceManager::~DeviceManager() {
    if (serial_port_ != nullptr) {
        closePort();
        delete serial_port_;
    }
    if (i2c_service_ != nullptr) {
        delete i2c_service_;
    }
    if (timer_ != nullptr) {
        timer_->stop();
        delete timer_;
    }
}

void DeviceManager::handleEchoMessage(const QByteArray& message) { qDebug() << "Echo closed: " << message; }

void DeviceManager::handleI2cMessage(const QByteArray& message) { i2c_service_->parseI2cResponse(message); }

void DeviceManager::run() {
    qDebug() << "Run in DeviceManager thread";
    i2c_service_ = new I2cService{ this };
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
            &DeviceManager::handleEchoMessage);
    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::i2cMessage, this,
            &DeviceManager::handleI2cMessage);

    timer_ = new QTimer{ this };
    connect(timer_, &QTimer::timeout, this, &DeviceManager::triggerEcho);
}

void DeviceManager::openPort(const QSerialPortInfo& port_info) {
    qDebug() << "Open port in DeviceManager thread";
    if (serial_port_ == nullptr || serial_port_->isOpen() == true) {
        return;
    }

    serial_port_->setPort(port_info);
    serial_port_->open(QIODevice::ReadWrite);
    emit openStateChanged(serial_port_->isOpen());

    if (EchoMessagesEnabled == true) {
        timer_->start(EchoMessagesPeriodMs);
    }
}

void DeviceManager::closePort() {
    qDebug() << "Close port in DeviceManager thread";
    if (serial_port_ == nullptr || serial_port_->isOpen() == false) {
        return;
    }

    timer_->stop();
    serial_port_->close();
    emit openStateChanged(serial_port_->isOpen());
}

void DeviceManager::sendI2cConfig(I2cConfig config) {
    qDebug() << "sendI2cConfig in DeviceManager thread";

    // Build message
    QByteArray message{ 128, 0 };
    if (i2c_service_->createI2cConfigMsg(config, message) == false) {
        qDebug() << "Failed to create I2C config message";
        return;
    }

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::I2cMsg, message);
}

void DeviceManager::sendI2cRequest(I2cRequest request) {
    qDebug() << "sendI2cRequest in DeviceManager thread";

    // Build message
    QByteArray message{ 128, 0 };
    if (i2c_service_->createI2cRequestMsg(request, message) == false) {
        qDebug() << "Failed to create I2C request message";
        return;
    }

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::I2cMsg, message);
}

void DeviceManager::triggerEcho() {
    QByteArray message{ "Who is John Galt? Who is Howard Roak?" };
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::EchoMsg, message);
}

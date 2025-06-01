#include "devicemanager.h"
#include <QDebug>
#include <QSerialPortInfo>
#include "magic_enum.hpp"
#include "plugins/device/driver/framedriver.h"

DeviceManager::DeviceManager(QObject* parent) : QObject{ parent } {}

DeviceManager::~DeviceManager() {
    if (serial_port_ != nullptr) {
        closePort();
        delete serial_port_;
    }
    if (ctrl_service_ != nullptr) {
        delete ctrl_service_;
    }
    if (i2c_service_ != nullptr) {
        delete i2c_service_;
    }
    if (firmware_installer_ != nullptr) {
        delete firmware_installer_;
    }
    if (timer_ != nullptr) {
        timer_->stop();
        delete timer_;
    }
}

void DeviceManager::handleEchoMessage(const QByteArray& message) { qDebug() << "Echo closed: " << message; }

void DeviceManager::handleCtrlMessage(const QByteArray& message) {
    CtrlRequest request;

    // Parse control message
    CtrlTypes::MessageType msg_type = ctrl_service_->parseCtrlResponse(message, request);
    if (msg_type == CtrlTypes::MessageType::DeviceInfo) {
        emit ctrlDeviceInfoReceived(request);
    } else {
        qDebug() << "Invalid CTRL message received!";
    }
}

void DeviceManager::handleI2cMessage(const QByteArray& message) {
    I2cConfig config;
    I2cRequest request;
    I2cNotification notification;

    // Parse I2C message
    I2cTypes::MessageType msg_type = i2c_service_->parseI2cResponse(message, config, request, notification);
    if (msg_type == I2cTypes::MessageType::ConfigStatus) {
        emit i2cConfigStatusReceived(config);
    } else if (msg_type == I2cTypes::MessageType::MasterStatus) {
        emit i2cRequestStatusReceived(request);
    } else if (msg_type == I2cTypes::MessageType::SlaveStatus) {
        emit i2cRequestStatusReceived(request);
    } else if (msg_type == I2cTypes::MessageType::SlaveNotification) {
        emit i2cSlaveNotificationReceived(notification);
    } else {
        qDebug() << "Invalid I2C message received!";
    }
}

void DeviceManager::triggerEcho() {
    QByteArray message{ "Who is John Galt? Who is Howard Roak?" };
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::EchoMsg, message);
}

void DeviceManager::run() {
    qDebug() << "Run in DeviceManager thread";
    i2c_service_ = new I2cService{ this };
    ctrl_service_ = new CtrlService{ this };
    firmware_installer_ = new FirmwareInstaller{ this };
    serial_port_ = new QSerialPort{ this };

    connect(serial_port_, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
        if (error != QSerialPort::SerialPortError::NoError) {
            qDebug() << "Serial port error: " << error;
            emit statusMessageChanged("[ERROR] Device not reachable!");
            closePort();
        }
    });

    connect(serial_port_, &QSerialPort::readyRead, this, [this]() {
        QByteArray data = serial_port_->readAll();
        driver::tf::FrameDriver::getInstance().receiveData(data);
    });

    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::sendData, this,
            [this](const QByteArray& data) {
                if (serial_port_ != nullptr && serial_port_->isOpen() == true) {
                    serial_port_->write(data);
                } else {
                    qDebug() << "Device not connected!";
                    emit statusMessageChanged("[ERROR] Device not connected!");
                }
            });

    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::echoMessage, this,
            &DeviceManager::handleEchoMessage);
    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::ctrlMessage, this,
            &DeviceManager::handleCtrlMessage);
    connect(&driver::tf::FrameDriver::getInstance(), &driver::tf::FrameDriver::i2cMessage, this,
            &DeviceManager::handleI2cMessage);

    connect(firmware_installer_, &FirmwareInstaller::stateChanged, this,
            [this](InstallerTypes::State state) { emit installerStateChanged(state); });

    connect(i2c_service_, &I2cService::statusMessage, this,
            [this](QString message) { emit statusMessageChanged(message); });

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

void DeviceManager::sendCtrlRequest(CtrlRequest request) {
    qDebug() << "sendCtrlRequest in DeviceManager thread";

    // Build message
    QByteArray message{ 128, 0 };
    if (ctrl_service_->createCtrlRequestMsg(request, message) == false) {
        qDebug() << "Failed to create CTRL request message!";
        return;
    }

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::CtrlMsg, message);
}

void DeviceManager::installFirmware(QString file) {
    qDebug() << "installFirmware in DeviceManager thread (file:" << file << ")";
    firmware_installer_->installFirmware(file);
}

void DeviceManager::sendI2cConfig(I2cConfig config) {
    qDebug() << "sendI2cConfig in DeviceManager thread";

    // Build message
    QByteArray message{ 256, 0 };
    if (i2c_service_->createI2cConfigMsg(config, message) == false) {
        qDebug() << "Failed to create I2C config message!";
        return;
    }

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::I2cMsg, message);
}

void DeviceManager::sendI2cRequest(I2cRequest request) {
    qDebug() << "sendI2cRequest in DeviceManager thread";

    // Build message
    QByteArray message{ 256, 0 };
    if (i2c_service_->createI2cRequestMsg(request, message) == false) {
        qDebug() << "Failed to create I2C request message!";
        return;
    }

    // Send message
    driver::tf::FrameDriver::getInstance().sendMessage(driver::tf::TfMsgType::I2cMsg, message);
}

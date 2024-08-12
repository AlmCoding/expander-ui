#include "interfaceexpander.h"

InterfaceExpander::InterfaceExpander(QObject* parent) : QObject{ parent } {
    com_thread_ = new QThread{ this };
    device_manager_ = new DeviceManager{ nullptr };
    device_manager_->moveToThread(com_thread_);

    connect(this, &InterfaceExpander::openPort, device_manager_, &DeviceManager::openPort);
    connect(this, &InterfaceExpander::closePort, device_manager_, &DeviceManager::closePort);

    connect(this, &InterfaceExpander::requestCtrl, device_manager_, &DeviceManager::sendCtrlRequest);
    connect(this, &InterfaceExpander::configI2c, device_manager_, &DeviceManager::sendI2cConfig);
    connect(this, &InterfaceExpander::requestI2c, device_manager_, &DeviceManager::sendI2cRequest);

    connect(device_manager_, &DeviceManager::openStateChanged, this, [this](bool open) {
        is_connected_ = open;
        emit isConnectedChanged(open);
    });

    connect(device_manager_, &DeviceManager::i2cConfigStatusReceived, this,
            [this](const I2cConfig& config) { emit i2cConfigStatusReceived(config); });
    connect(device_manager_, &DeviceManager::i2cRequestStatusReceived, this, [this](const I2cRequest& request) {
        if (log_model_ != nullptr) {
            log_model_->appendNewLog(request);
        } else {
            emit i2cRequestStatusReceived(request);
        }
    });
    connect(device_manager_, &DeviceManager::i2cSlaveNotificationReceived, this,
            [this](const I2cNotification& notification) {
                if (log_model_ != nullptr) {
                    log_model_->appendNewLog(notification);
                } else {
                    emit i2cSlaveNotificationReceived(notification);
                }
            });

    connect(com_thread_, &QThread::started, device_manager_, &DeviceManager::run);
    com_thread_->start();
}

InterfaceExpander::~InterfaceExpander() {
    com_thread_->quit();
    com_thread_->wait();
    delete device_manager_;
}

void InterfaceExpander::sendCtrlRequest(bool get_device_info, bool reset_device, bool start_bootloader) {
    CtrlRequest request;
    request.setGetDeviceInfo(get_device_info);
    request.setResetDevice(reset_device);
    request.setStartBootloader(start_bootloader);
    emit requestCtrl(request);
}

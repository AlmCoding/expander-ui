#include "interfaceexpander.h"

InterfaceExpander::InterfaceExpander(QObject* parent) : QObject{ parent } {
    com_thread_ = new QThread{ this };
    device_manager_ = new DeviceManager{ nullptr };
    device_manager_->moveToThread(com_thread_);

    connect(this, &InterfaceExpander::openPort, device_manager_, &DeviceManager::openPort);
    connect(this, &InterfaceExpander::closePort, device_manager_, &DeviceManager::closePort);

    connect(this, &InterfaceExpander::requestCtrl, device_manager_, &DeviceManager::sendCtrlRequest);
    connect(this, &InterfaceExpander::updateFirmware, device_manager_, &DeviceManager::installFirmware);
    connect(this, &InterfaceExpander::configI2c, device_manager_, &DeviceManager::sendI2cConfig);
    connect(this, &InterfaceExpander::requestI2c, device_manager_, &DeviceManager::sendI2cRequest);

    connect(device_manager_, &DeviceManager::openStateChanged, this, [this](bool open) {
        is_connected_ = open;
        hw_version_ = "N/A";
        fw_version_ = "N/A";
        git_hash_ = "N/A";
        emit isConnectedChanged(open);
        emit hwVersionChanged(hw_version_);
        emit fwVersionChanged(fw_version_);
        emit gitHashChanged(git_hash_);
    });

    connect(device_manager_, &DeviceManager::installerStateChanged, this, [this](InstallerTypes::State state) {
        installer_state_ = state;
        emit installerStateChanged(state);
    });

    connect(device_manager_, &DeviceManager::ctrlDeviceInfoReceived, this, [this](const CtrlRequest& request) {
        hw_version_ = QString::number(request.getDeviceInfo().getHardwareVersion());
        fw_version_ = QString::number(request.getDeviceInfo().getFirmwareVersionMajor()) + "." +
                      QString::number(request.getDeviceInfo().getFirmwareVersionMinor()) + "." +
                      QString::number(request.getDeviceInfo().getFirmwareVersionPatch());
        git_hash_ = request.getDeviceInfo().getGitHash().left(7);
        emit hwVersionChanged(hw_version_);
        emit fwVersionChanged(fw_version_);
        emit gitHashChanged(git_hash_);
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

void InterfaceExpander::sendCtrlGetDeviceInfo() {
    CtrlRequest request;
    request.setGetDeviceInfo(true);
    emit requestCtrl(request);
}

void InterfaceExpander::sendCtrlResetDevice() {
    CtrlRequest request;
    request.setResetDevice(true);
    emit requestCtrl(request);
}

void InterfaceExpander::sendCtrlStartBootloader() {
    CtrlRequest request;
    request.setStartBootloader(true);
    emit requestCtrl(request);
}

void InterfaceExpander::startFirmwareUpdate(QString file) { emit updateFirmware(file); }

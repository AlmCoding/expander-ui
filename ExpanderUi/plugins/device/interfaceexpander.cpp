#include "interfaceexpander.h"

InterfaceExpander::InterfaceExpander(QObject* parent) : QObject{ parent } {
    com_thread_ = new QThread{ this };
    device_com_ = new DeviceCom{ nullptr };
    device_com_->moveToThread(com_thread_);

    connect(this, &InterfaceExpander::openPort, device_com_, &DeviceCom::openPort);
    connect(this, &InterfaceExpander::closePort, device_com_, &DeviceCom::closePort);
    connect(this, &InterfaceExpander::configI2c, device_com_, &DeviceCom::sendI2cConfig);
    connect(this, &InterfaceExpander::requestI2c, device_com_, &DeviceCom::sendI2cRequest);

    connect(device_com_, &DeviceCom::openStateChanged, this, [this](bool open) {
        is_connected_ = open;
        emit isConnectedChanged(open);
    });

    connect(com_thread_, &QThread::started, device_com_, &DeviceCom::run);
    com_thread_->start();
}

InterfaceExpander::~InterfaceExpander() {
    com_thread_->quit();
    com_thread_->wait();
    delete device_com_;
}

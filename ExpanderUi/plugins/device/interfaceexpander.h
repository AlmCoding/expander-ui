#ifndef INTERFACEEXPANDER_H
#define INTERFACEEXPANDER_H

#include <QDebug>
#include <QObject>
#include <QSerialPortInfo>
#include <QThread>
#include "plugins/containers/i2c/i2cconfig.h"
#include "plugins/containers/i2c/i2crequest.h"
#include "plugins/containers/i2c/i2ctypes.h"
#include "plugins/device/devicemanager.h"
#include "plugins/i2clogmodel.h"

class InterfaceExpander : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isConnected READ getIsConnected NOTIFY isConnectedChanged)

   public:
    explicit InterfaceExpander(QObject* parent = nullptr);
    ~InterfaceExpander();

   public slots:
    bool getIsConnected() const { return is_connected_; }
    void sendOpenPort(const QSerialPortInfo& port_info) { emit openPort(port_info); }
    void sendClosePort() { emit closePort(); }

    void sendCtrlRequest(bool get_device_info, bool reset_device, bool start_bootloader);
    void sendI2cConfig(I2cConfig config) { emit configI2c(config); }
    void sendI2cRequest(I2cRequest request, I2cTypes::I2cId interface) {
        request.setI2cId(interface);
        emit requestI2c(request);
    }

    void setI2cLogModel(I2cLogModel* log_model) {
        qDebug() << "setI2cLogModel: " << log_model;
        log_model_ = log_model;
    }

   signals:
    void isConnectedChanged(bool connected);
    void openPort(const QSerialPortInfo& port_info);
    void closePort();
    void requestCtrl(const CtrlRequest& request);
    void configI2c(const I2cConfig& config);
    void requestI2c(const I2cRequest& request);

    void i2cConfigStatusReceived(const I2cConfig& config);
    void i2cRequestStatusReceived(const I2cRequest& request);
    void i2cSlaveNotificationReceived(const I2cNotification& notification);

   private:
    QThread* com_thread_ = nullptr;
    DeviceManager* device_manager_ = nullptr;
    bool is_connected_ = false;

    I2cLogModel* log_model_ = nullptr;
};

#endif  // INTERFACEEXPANDER_H

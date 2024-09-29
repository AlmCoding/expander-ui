#ifndef INTERFACEEXPANDER_H
#define INTERFACEEXPANDER_H

#include <QDebug>
#include <QObject>
#include <QSerialPortInfo>
#include <QThread>
#include <QString>
#include "plugins/containers/i2c/i2cconfig.h"
#include "plugins/containers/i2c/i2crequest.h"
#include "plugins/containers/i2c/i2ctypes.h"
#include "plugins/device/devicemanager.h"
#include "plugins/i2clogmodel.h"

class InterfaceExpander : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isConnected READ getIsConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString fwVersion READ getFwVersion NOTIFY fwVersionChanged)
    Q_PROPERTY(QString hwVersion READ getHwVersion NOTIFY hwVersionChanged)

   public:
    explicit InterfaceExpander(QObject* parent = nullptr);
    ~InterfaceExpander();

   public slots:
    bool getIsConnected() const { return is_connected_; }
    QString getFwVersion() const { return fw_version_; }
    QString getHwVersion() const { return hw_version_; }
    void sendOpenPort(const QSerialPortInfo& port_info) { emit openPort(port_info); }
    void sendClosePort() { emit closePort(); }

    void sendCtrlGetDeviceInfo();
    void sendCtrlResetDevice();
    void sendCtrlStartBootloader();
    void startFirmwareUpdate(QString file);

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
    void fwVersionChanged(QString fw_version);
    void hwVersionChanged(QString hw_version);
    void openPort(const QSerialPortInfo& port_info);
    void closePort();
    void updateFirmware(QString file);
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
    QString fw_version_{ "N/A" };
    QString hw_version_{ "N/A" };

    I2cLogModel* log_model_ = nullptr;
};

#endif  // INTERFACEEXPANDER_H

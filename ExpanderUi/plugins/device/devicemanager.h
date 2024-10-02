#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include "plugins/containers/com/installertypes.h"
#include "plugins/containers/ctrl/ctrlrequest.h"
#include "plugins/containers/i2c/i2cconfig.h"
#include "plugins/containers/i2c/i2cnotification.h"
#include "plugins/containers/i2c/i2crequest.h"
#include "plugins/device/ctrlservice.h"
#include "plugins/device/firmwareinstaller.h"
#include "plugins/device/i2cservice.h"

constexpr bool EchoMessagesEnabled = false;
constexpr int EchoMessagesPeriodMs = 10;

class DeviceManager : public QObject {
    Q_OBJECT

   public:
    explicit DeviceManager(QObject* parent = nullptr);
    ~DeviceManager();

   private slots:
    void handleEchoMessage(const QByteArray& message);
    void handleCtrlMessage(const QByteArray& message);
    void handleI2cMessage(const QByteArray& message);
    void triggerEcho();

   public slots:
    void run();

    void openPort(const QSerialPortInfo& port_info);
    void closePort();

    void sendCtrlRequest(CtrlRequest request);
    void installFirmware(QString file);
    void sendI2cConfig(I2cConfig config);
    void sendI2cRequest(I2cRequest request);

   signals:
    void openStateChanged(bool open);
    void installerStateChanged(InstallerTypes::State state);
    void ctrlDeviceInfoReceived(CtrlRequest request);
    void i2cConfigStatusReceived(I2cConfig config);
    void i2cRequestStatusReceived(I2cRequest request);
    void i2cSlaveNotificationReceived(I2cNotification notification);

   private:
    QSerialPort* serial_port_ = nullptr;
    CtrlService* ctrl_service_ = nullptr;
    I2cService* i2c_service_ = nullptr;
    FirmwareInstaller* firmware_installer_ = nullptr;
    QTimer* timer_ = nullptr;
};

#endif  // DEVICEMANAGER_H

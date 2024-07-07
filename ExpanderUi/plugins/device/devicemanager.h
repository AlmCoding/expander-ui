#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2crequest.h"
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
    void handleI2cMessage(const QByteArray& message);
    void triggerEcho();

   public slots:
    void run();

    void openPort(const QSerialPortInfo& port_info);
    void closePort();

    void sendI2cConfig(I2cConfig config);
    void sendI2cRequest(I2cRequest request);

   signals:
    void openStateChanged(bool open);
    void i2cConfigStatusReceived(I2cConfig config);
    void i2cRequestStatusReceived(I2cRequest request);

   private:
    QSerialPort* serial_port_ = nullptr;
    I2cService* i2c_service_ = nullptr;
    QTimer* timer_ = nullptr;
};

#endif  // DEVICEMANAGER_H

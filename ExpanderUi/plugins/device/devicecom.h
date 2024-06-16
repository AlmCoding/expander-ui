#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2crequest.h"

class DeviceCom : public QObject {
    Q_OBJECT

   public:
    explicit DeviceCom(QObject* parent = nullptr);
    ~DeviceCom();

   private slots:
    void handleEchoMessage(const QByteArray& data);
    void handleI2cMessage(const QByteArray& data);

   public slots:
    void run();

    void openPort(const QSerialPortInfo& port_info);
    void closePort();

    void sendI2cConfig(I2cConfig config);
    void sendI2cRequest(I2cRequest request);

   signals:
    void openStateChanged(bool open);

   private slots:
    void triggerEcho();

   private:
    QSerialPort* serial_port_ = nullptr;
    QTimer* timer_ = nullptr;
};

#endif  // DEVICECOM_H

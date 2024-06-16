#ifndef INTERFACEEXPANDER_H
#define INTERFACEEXPANDER_H

#include <QDebug>
#include <QObject>
#include <QSerialPortInfo>
#include <QThread>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2crequest.h"
#include "plugins/device/devicecom.h"

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

    void sendI2cConfig(I2cConfig config) { emit configI2c(config); }
    void sendI2cRequest(I2cRequest request) { emit requestI2c(request); }

   signals:
    void openPort(const QSerialPortInfo& port_info);
    void closePort();
    void configI2c(const I2cConfig& config);
    void requestI2c(const I2cRequest& request);

    void isConnectedChanged(bool connected);

   private:
    QThread* com_thread_ = nullptr;
    DeviceCom* device_com_ = nullptr;
    bool is_connected_ = false;
};

#endif  // INTERFACEEXPANDER_H

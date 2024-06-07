#ifndef INTERFACEEXPANDER_H
#define INTERFACEEXPANDER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QThread>
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

   signals:
    void openPort(const QSerialPortInfo& port_info);
    void closePort();

    void isConnectedChanged(bool connected);

   private:
    QThread* com_thread_ = nullptr;
    DeviceCom* device_com_ = nullptr;
    bool is_connected_ = false;
};

#endif  // INTERFACEEXPANDER_H

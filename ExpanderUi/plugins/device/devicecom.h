#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class DeviceCom : public QObject {
    Q_OBJECT

   public:
    explicit DeviceCom(QObject* parent = nullptr);

   public slots:
    void run();

    void openPort(const QSerialPortInfo& port_info);
    void closePort();

   signals:
    void openStateChanged(bool open);

   private:
    QSerialPort* serial_port_ = nullptr;
    bool is_open_ = false;
};

#endif  // DEVICECOM_H

#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

class DeviceCom : public QObject {
    Q_OBJECT

   public:
    explicit DeviceCom(QObject* parent = nullptr);
    ~DeviceCom();

   public slots:
    void run();

    void openPort(const QSerialPortInfo& port_info);
    void closePort();

   signals:
    void openStateChanged(bool open);

   private slots:
    void triggerEcho();

   private:
    QSerialPort* serial_port_ = nullptr;
    QTimer* timer_ = nullptr;
};

#endif  // DEVICECOM_H

#include "devicecom.h"
#include <QDebug>
#include <QSerialPortInfo>

DeviceCom::DeviceCom(QObject* parent) : QThread{ parent } {}

void DeviceCom::run() {
    qDebug() << "Run in DeviceCom thread";

    exec();
}

#include "i2cconfig.h"
#include <QDebug>


I2cConfig::I2cConfig(QObject *parent)
    : QObject{parent}
{}

void I2cConfig::applyConfig()
{
    qDebug() << "TODO: Apply config";
}

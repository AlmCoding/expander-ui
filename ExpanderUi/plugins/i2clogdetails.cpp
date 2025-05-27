#include "i2clogdetails.h"

I2cLogDetails::I2cLogDetails(QObject* parent) : QObject{ parent } {}

void I2cLogDetails::setVisible(bool visible) {
    visible_ = visible;
    emit visibleChanged(visible_);
}

void I2cLogDetails::loadLog(const I2cLog& log) {
    log_ = log;
    emit timeChanged(log.getTime());
    emit interfaceChanged(log.getInterfaceName());
    emit typeChanged((log.getType() == I2cTypes::I2cReqestType::MasterAction) ? "MR" : "SC");
    emit nameChanged(log.getName());
    emit slaveAddrChanged(log.getSlaveAddr());
    emit writeDataChanged(log.getWriteData());
    emit writeDataAsciiChanged(log.getWriteDataAscii());
    emit readDataChanged(log.getReadData());
    emit readDataAsciiChanged(log.getReadDataAscii());
    emit writeSizeChanged(log.getWriteSize());
    emit readSizeChanged(log.getReadSize());
    emit statusChanged(log.getStatus());
}

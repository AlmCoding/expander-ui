#include "i2crequest.h"

I2cRequest::I2cRequest(I2cTypes::I2cReqestType type, QString name, QString slave_addr, QString write_data,
                       QString read_size)
    : type_{ type }, name_{ name }, slave_addr_{ slave_addr }, write_data_{ write_data }, read_size_{ read_size } {}

QString I2cRequest::getWriteSize() const {
    QString write_data = write_data_;
    int size = write_data.remove(' ').length();
    QString size_str = QString::number(size / 2);
    return size_str;
}

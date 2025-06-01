#include "i2crequestform.h"
#include "plugins/utility.h"

I2cRequestForm::I2cRequestForm(QObject* parent) : QObject{ parent } {}

void I2cRequestForm::setVisible(bool visible) {
    visible_ = visible;
    emit visibleChanged(visible_);
}

void I2cRequestForm::setExternalUpdate(bool external_update) {
    external_update_ = external_update;
    emit externalUpdateChanged(external_update_);
}

void I2cRequestForm::setHexUpdate(bool hex_update) {
    hex_update_ = hex_update;
    emit hexUpdateChanged(hex_update_);
}

void I2cRequestForm::setAsciiUpdate(bool ascii_update) {
    ascii_update_ = ascii_update;
    emit asciiUpdateChanged(ascii_update_);
}

void I2cRequestForm::setType(I2cTypes::I2cReqestType type) {
    bool changed = false;

    if (type_ != type) {
        type_ = type;
        emit typeChanged(type_);
        changed = true;
    }

    request_.setType(type_);
    if (changed == true && external_update_ == false) {
        emit requestChanged(request_);
    }
}

void I2cRequestForm::setName(const QString& name) {
    name_ = name;
    emit nameChanged(name_);

    request_.setName(name_);
    if (external_update_ == false) emit requestChanged(request_);
}

void I2cRequestForm::setSlaveAddress(const QString& slave_addr) {
    slave_addr_ = slave_addr;
    emit slaveAddressChanged(slave_addr_);

    request_.setSlaveAddr(slave_addr_);
    if (external_update_ == false) emit requestChanged(request_);
}

void I2cRequestForm::setWriteData(const QString& write_data) {
    if (ascii_update_ == false) hex_update_ = true;
    write_data_ = write_data;
    emit writeDataChanged(write_data_);

    if (hex_update_ == true) {
        write_data_ascii_ = Utility::convertHexToAscii(write_data_);
        emit writeDataAsciiChanged(write_data_ascii_);
    }

    request_.setWriteData(write_data_);
    setWriteSize(request_.getWriteSize());
    if (external_update_ == false) emit requestChanged(request_);
    hex_update_ = false;
}

void I2cRequestForm::setWriteDataAscii(const QString& write_data_ascii) {
    if (hex_update_ == false) ascii_update_ = true;
    write_data_ascii_ = write_data_ascii;
    emit writeDataAsciiChanged(write_data_ascii_);

    if (ascii_update_ == true) {
        write_data_ = Utility::convertAsciiToHex(write_data_ascii_);
        emit writeDataChanged(write_data_);
    }

    request_.setWriteData(write_data_);
    setWriteSize(request_.getWriteSize());
    if (external_update_ == false) emit requestChanged(request_);
    ascii_update_ = false;
}

void I2cRequestForm::setWriteSize(const QString& write_size) {
    write_size_ = write_size;
    emit writeSizeChanged(write_size_);
}

void I2cRequestForm::setReadSize(const QString& read_size) {
    read_size_ = read_size;
    emit readSizeChanged(read_size_);

    request_.setReadSize(read_size_);
    if (external_update_ == false) emit requestChanged(request_);
}

void I2cRequestForm::loadRequest(const I2cRequest& request) {
    request_ = request;

    external_update_ = true;
    setType(request.getType());
    setName(request.getName());
    setSlaveAddress(request.getSlaveAddr());
    setWriteData(request.getWriteData());
    setReadSize(request.getReadSize());
    external_update_ = false;
}

void I2cRequestForm::clearRequest() {
    I2cRequest request{};
    request.setType(request_.getType());
    request.setName(request_.getName());
    request.setSlaveAddr(request_.getSlaveAddr());
    request.setReadSize(QString{ "0" });
    loadRequest(request);
    emit requestChanged(request_);
}

#ifndef I2CLOG_H
#define I2CLOG_H

#include <QString>
#include "plugins/containers/i2c/i2ctypes.h"

class I2cLog {
   public:
    explicit I2cLog() = default;
    explicit I2cLog(QString time, QString interface_name, I2cTypes::I2cReqestType type, QString name, QString slave_address,
                    QString write_data, QString read_data, QString write_size, QString read_size, QString status);

    void setTime(QString time) { time_ = time; }
    void setInterfaceName(QString interface_name) { interface_name_ = interface_name; }
    void setType(I2cTypes::I2cReqestType type) { type_ = type; }
    void setName(QString name) { name = name; }
    void setSlaveAddr(QString slave_addr) { slave_addr_ = slave_addr; }
    void setWriteData(QString write_data) { write_data_ = write_data; }
    void setReadData(QString read_data) { read_data_ = read_data; }
    void setWriteSize(QString write_size) { write_size_ = write_size; }
    void setReadSize(QString read_size) { read_size_ = read_size; }
    void setStatus(QString status) { status_ = status; }

    QString getTime() const { return time_; }
    QString getInterfaceName() const { return interface_name_; }
    I2cTypes::I2cReqestType getType() const { return type_; }
    QString getName() const { return name; }
    QString getSlaveAddr() const { return slave_addr_; }
    QString getWriteData() const { return write_data_; }
    QString getReadData() const { return read_data_; }
    QString getWriteSize() const { return write_size_; }
    QString getReadSize() const { return read_size_; }
    QString getStatus() const { return status_; }

   private:
    QString time_;
    QString interface_name_;
    I2cTypes::I2cReqestType type_;
    QString name;
    QString slave_addr_;
    QString write_data_;
    QString read_data_;
    QString write_size_;
    QString read_size_;
    QString status_;
};

#endif  // I2CLOG_H

#ifndef I2CREQUEST_H
#define I2CREQUEST_H

#include <QString>
#include "plugins/containers/i2crequeststatus.h"
#include "plugins/containers/i2ctypes.h"

class I2cRequest {
   public:
    explicit I2cRequest() = default;
    explicit I2cRequest(I2cTypes::I2cReqestType type, QString name, QString slave_addr, QString write_data,
                        QString read_size);

    void setRequestId(int request_id) { request_id_ = request_id; }
    void setI2cId(I2cTypes::I2cId i2c_id) { i2c_id_ = i2c_id; }
    void setName(QString name) { name_ = name; }
    void setType(I2cTypes::I2cReqestType type) { type_ = type; }
    void setSlaveAddr(QString slave_addr) { slave_addr_ = slave_addr; }
    void setWriteData(QString write_data) { write_data_ = write_data; }
    void setReadSize(QString read_size) { read_size_ = read_size; }
    void setStatus(I2cRequestStatus& status) { status_ = status; }

    int getRequestId() const { return request_id_; }
    I2cTypes::I2cId getI2cId() const { return i2c_id_; }
    I2cTypes::I2cReqestType getType() const { return type_; }
    QString getName() const { return name_; }
    QString getSlaveAddr() const { return slave_addr_; }
    QString getWriteData() const { return write_data_; }
    QString getWriteSize() const;
    QString getReadSize() const { return read_size_; }
    I2cRequestStatus getStatus() const { return status_; }

   private:
    int request_id_ = -1;
    I2cTypes::I2cId i2c_id_ = I2cTypes::I2cId::Undefined;
    I2cTypes::I2cReqestType type_ = I2cTypes::I2cReqestType::MasterAction;
    QString name_;
    QString slave_addr_;
    QString write_data_;
    QString read_size_;

    I2cRequestStatus status_;
};

#endif  // I2CREQUEST_H

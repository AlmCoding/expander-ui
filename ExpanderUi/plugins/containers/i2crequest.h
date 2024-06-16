#ifndef I2CREQUEST_H
#define I2CREQUEST_H

#include <QString>

enum class I2cReqestType {
    MasterAction = 0,
    SlaveConfig,
};

class I2cRequest {
   public:
    explicit I2cRequest() = default;
    explicit I2cRequest(I2cReqestType type, QString name, QString slave_addr, QString write_data, QString read_size);

    void setName(QString name) { name_ = name; }
    void setType(I2cReqestType type) { type_ = type; }
    void setSlaveAddr(QString slave_addr) { slave_addr_ = slave_addr; }
    void setWriteData(QString write_data) { write_data_ = write_data; }
    void setReadSize(QString read_size) { read_size_ = read_size; }

    I2cReqestType getType() const { return type_; }
    QString getName() const { return name_; }
    QString getSlaveAddr() const { return slave_addr_; }
    QString getWriteData() const { return write_data_; }
    QString getWriteSize() const;
    QString getReadSize() const { return read_size_; }

   private:
    I2cReqestType type_;
    QString name_;
    QString slave_addr_;
    QString write_data_;
    QString read_size_;
};

#endif  // I2CREQUEST_H

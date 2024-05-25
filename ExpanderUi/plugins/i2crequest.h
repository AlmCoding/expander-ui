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
    explicit I2cRequest(I2cReqestType type, QString name, int slave_add, QByteArray write_data, int read_size);

    void setName(QString name) { name_ = name; }
    void setType(I2cReqestType type) { type_ = type; }
    void setSlaveAddr(int slave_addr) { slave_addr_ = slave_addr; }
    void setWriteData(QByteArray write_data) { write_data_ = write_data; }
    void setReadSize(int read_size) { read_size_ = read_size; }

    I2cReqestType getType() const { return type_; }
    QString getName() const { return name_; }
    int getSlaveAddr() const { return slave_addr_; }
    QByteArray getWriteData() const { return write_data_; }
    int getReadSize() const { return read_size_; }

   private:
    I2cReqestType type_;
    QString name_;
    int slave_addr_ = 0;
    QByteArray write_data_;
    int read_size_ = 0;
};

#endif  // I2CREQUEST_H

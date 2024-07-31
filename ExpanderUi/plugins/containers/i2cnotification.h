#ifndef I2CNOTIFICATION_H
#define I2CNOTIFICATION_H

#include <QString>
#include "plugins/containers/i2ctypes.h"

class I2cNotification {
   public:
    I2cNotification() = default;
    I2cNotification(int access_id, I2cTypes::StatusCode status_code, const QString& write_data,
                    const QString& read_data);

    void setAccessId(int access_id) { access_id_ = access_id; }
    void setI2cId(I2cTypes::I2cId i2c_id) { i2c_id_ = i2c_id; }
    void setStatusCode(I2cTypes::StatusCode status_code) { status_code_ = status_code; }
    void setWriteData(const QString& write_data) { write_data_ = write_data; }
    void setReadData(const QString& read_data) { read_data_ = read_data; }

    int getAccessId() const { return access_id_; }
    I2cTypes::I2cId getI2cId() const { return i2c_id_; }
    I2cTypes::StatusCode getStatusCode() const { return status_code_; }
    QString getWriteData() const { return write_data_; }
    QString getReadData() const { return read_data_; }
    QString getWriteSize() const;
    QString getReadSize() const;

   private:
    int access_id_ = -1;
    I2cTypes::I2cId i2c_id_ = I2cTypes::I2cId::Undefined;
    I2cTypes::StatusCode status_code_ = I2cTypes::StatusCode::NotInit;

    QString write_data_;
    QString read_data_;
};

#endif  // I2CNOTIFICATION_H

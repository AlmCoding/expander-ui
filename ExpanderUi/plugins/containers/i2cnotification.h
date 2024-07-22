#ifndef I2CNOTIFICATION_H
#define I2CNOTIFICATION_H

#include <QString>
#include "plugins/containers/i2ctypes.h"

class I2cNotification {
   public:
    I2cNotification() = default;
    I2cNotification(int access_id, I2cTypes::StatusCode status_code, const QString& read_addr, const QString& read_size,
                    const QString& write_addr, const QString& write_data);

    void setAccessId(int access_id) { access_id = access_id; }
    void setStatusCode(I2cTypes::StatusCode status_code) { status_code_ = status_code; }
    void setReadAddr(const QString& read_addr) { read_addr_ = read_addr; }
    void setReadSize(const QString& read_size) { read_size_ = read_size; }
    void setWriteAddr(const QString& write_addr) { write_addr_ = write_addr; }
    void setWriteData(const QString& write_data) { write_data_ = write_data; }

    int getAccessId() const { return access_id; }
    I2cTypes::StatusCode getStatusCode() const { return status_code_; }
    QString getReadAddr() const { return read_addr_; }
    QString getReadSize() const { return read_size_; }
    QString getWriteAddr() const { return write_addr_; }
    QString getWriteData() const { return write_data_; }

   private:
    int access_id = -1;
    I2cTypes::StatusCode status_code_ = I2cTypes::StatusCode::NotInit;

    QString read_addr_;
    QString read_size_;

    QString write_addr_;
    QString write_data_;
};

#endif  // I2CNOTIFICATION_H

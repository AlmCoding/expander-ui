#ifndef I2CREQUESTSTATUS_H
#define I2CREQUESTSTATUS_H

#include <QDataStream>
#include <QString>
#include "plugins/containers/i2c/i2ctypes.h"

class I2cRequestStatus {
   public:
    I2cRequestStatus() = default;
    I2cRequestStatus(int request_id, I2cTypes::StatusCode status_code, int nack_idx, const QString& read_data);

    void setRequestId(int request_id) { request_id_ = request_id; }
    void setI2cId(I2cTypes::I2cId i2c_id) { i2c_id_ = i2c_id; }
    void setStatusCode(I2cTypes::StatusCode status_code) { status_code_ = status_code; }
    void setNackIdx(int nack_idx) { nack_idx_ = nack_idx; }
    void setReadData(const QString& read_data) { read_data_ = read_data; }

    int getRequestId() const { return request_id_; }
    I2cTypes::I2cId getI2cId() const { return i2c_id_; }
    I2cTypes::StatusCode getStatusCode() const { return status_code_; }
    int getNackIdx() const { return nack_idx_; }
    QString getReadData() const { return read_data_; }
    QString getReadSize() const;

    friend QDataStream& operator<<(QDataStream& out, const I2cRequestStatus& request);
    friend QDataStream& operator>>(QDataStream& in, I2cRequestStatus& request);

   private:
    int request_id_ = -1;
    I2cTypes::I2cId i2c_id_ = I2cTypes::I2cId::Undefined;
    I2cTypes::StatusCode status_code_ = I2cTypes::StatusCode::NotInit;
    int nack_idx_ = -1;
    QString read_data_;
};

#endif  // I2CREQUESTSTATUS_H

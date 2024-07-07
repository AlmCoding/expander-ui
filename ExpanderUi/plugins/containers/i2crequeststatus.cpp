#include "i2crequeststatus.h"

I2cRequestStatus::I2cRequestStatus(int request_id, StatusCode status_code, const QString& read_data)
    : request_id_{ request_id }, status_code_{ status_code }, read_data_{ read_data } {}

QString I2cRequestStatus::getReadSize() const {
    QString read_data = read_data_;
    int size = read_data.remove(' ').length();
    QString size_str = QString::number(size / 2);
    return size_str;
}

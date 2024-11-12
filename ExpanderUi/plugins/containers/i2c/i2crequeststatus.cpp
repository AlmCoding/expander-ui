#include "i2crequeststatus.h"

I2cRequestStatus::I2cRequestStatus(int request_id, I2cTypes::StatusCode status_code, const QString& read_data)
    : request_id_{ request_id }, status_code_{ status_code }, read_data_{ read_data } {}

QString I2cRequestStatus::getReadSize() const {
    QString read_data = read_data_;
    int size = read_data.remove(' ').length();
    QString size_str = QString::number(size / 2);
    return size_str;
}

QDataStream& operator<<(QDataStream& out, const I2cRequestStatus& request) {
    out << request.request_id_                     //
        << static_cast<int>(request.i2c_id_)       //
        << static_cast<int>(request.status_code_)  //
        << request.read_data_;                     //
    return out;
}

QDataStream& operator>>(QDataStream& in, I2cRequestStatus& request) {
    int i2c_id;
    int status_code;
    in >> request.request_id_   //
        >> i2c_id               //
        >> status_code          //
        >> request.read_data_;  //
    request.i2c_id_ = static_cast<I2cTypes::I2cId>(i2c_id);
    request.status_code_ = static_cast<I2cTypes::StatusCode>(status_code);
    return in;
}
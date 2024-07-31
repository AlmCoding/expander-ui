#include "i2cnotification.h"

I2cNotification::I2cNotification(int access_id, I2cTypes::StatusCode status_code, const QString& write_data,
                                 const QString& read_data)
    : access_id_{ access_id },
      status_code_{ status_code },
      write_data_{ write_data },
      read_data_{ read_data } {}

QString I2cNotification::getWriteSize() const {
    QString write_data = write_data_;
    int size = write_data.remove(' ').length();
    QString size_str = QString::number(size / 2);
    return size_str;
}

QString I2cNotification::getReadSize() const {
    QString read_data = read_data_;
    int size = read_data.remove(' ').length();
    QString size_str = QString::number(size / 2);
    return size_str;
}

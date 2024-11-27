#include "i2clog.h"

I2cLog::I2cLog(QString time, QString interface_name, I2cTypes::I2cReqestType type, QString name, QString slave_addr,
               QString write_data, QString read_data, QString write_size, QString read_size, QString status)
    : time_(time),
      interface_name_(interface_name),
      type_(type),
      name(name),
      slave_addr_(slave_addr),
      write_data_(write_data),
      read_data_(read_data),
      write_size_(write_size),
      read_size_(read_size),
      status_(status) {}

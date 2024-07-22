#include "i2cnotification.h"

I2cNotification::I2cNotification(int access_id, I2cTypes::StatusCode status_code, const QString& read_addr,
                                 const QString& read_size, const QString& write_addr, const QString& write_data)
    : access_id{ access_id },
      status_code_{ status_code },
      read_addr_{ read_addr },
      read_size_{ read_size },
      write_addr_{ write_addr },
      write_data_{ write_data } {}

#include "i2cconfig.h"
#include <QDebug>

I2cConfig::I2cConfig(I2cTypes::I2cId i2c_id, QString slave_addr, I2cTypes::ClockFreq clock_freq,
                     I2cTypes::MemAddrWidth mem_addr_width, I2cTypes::SlaveAddrWidth slave_addr_width)
    : i2c_id_(i2c_id),
      slave_addr_(slave_addr),
      clock_freq_(clock_freq),
      mem_addr_width_(mem_addr_width),
      slave_addr_width_(slave_addr_width) {}

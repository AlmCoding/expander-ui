#ifndef I2CCONFIG_H
#define I2CCONFIG_H

#include <QString>
#include "plugins/containers/i2cconfigstatus.h"
#include "plugins/containers/i2ctypes.h"

class I2cConfig {
   public:
    explicit I2cConfig();

    int request_id = -1;
    I2cTypes::I2cId i2c_id = I2cTypes::I2cId::Undefined;
    QString slave_addr = "0x001";
    I2cTypes::ClockFreq clock_freq = I2cTypes::ClockFreq::KHz10;
    I2cTypes::MemAddrWidth mem_addr_width = I2cTypes::MemAddrWidth::OneByte;
    I2cTypes::SlaveAddrWidth slave_addr_width = I2cTypes::SlaveAddrWidth::SevenBit;

    I2cConfigStatus status;
};

#endif  // I2CCONFIG_H

#ifndef I2CCONFIG_H
#define I2CCONFIG_H

#include <QString>

namespace I2cConfigTypes {
Q_NAMESPACE

enum class I2cId {
    I2c0 = 0,
    I2c1,
    Undefined,
};
enum class ClockFreq {
    KHz10 = 0,
    KHz100,
    KHz400,
    KHz1000,
};
enum class MemAddrWidth {
    OneByte = 0,
    TwoByte,
};
enum class SlaveAddrWidth {
    SevenBit = 0,
    TenBit,
};

Q_ENUM_NS(I2cId)
Q_ENUM_NS(ClockFreq)
Q_ENUM_NS(MemAddrWidth)
Q_ENUM_NS(SlaveAddrWidth)

}  // namespace I2cConfigTypes

class I2cConfig {
   public:
    explicit I2cConfig();

    I2cConfigTypes::I2cId i2c_id = I2cConfigTypes::I2cId::Undefined;
    QString slave_addr = "0x001";
    I2cConfigTypes::ClockFreq clock_freq = I2cConfigTypes::ClockFreq::KHz10;
    I2cConfigTypes::MemAddrWidth mem_addr_width = I2cConfigTypes::MemAddrWidth::OneByte;
    I2cConfigTypes::SlaveAddrWidth slave_addr_width = I2cConfigTypes::SlaveAddrWidth::SevenBit;
};

#endif  // I2CCONFIG_H

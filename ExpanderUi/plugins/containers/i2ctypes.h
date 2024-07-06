#ifndef I2CTYPES_H
#define I2CTYPES_H

#include <QObject>

namespace I2cTypes {
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
enum class I2cReqestType {
    MasterAction = 0,
    SlaveConfig,
    Undefined,
};

Q_ENUM_NS(I2cId)
Q_ENUM_NS(ClockFreq)
Q_ENUM_NS(MemAddrWidth)
Q_ENUM_NS(SlaveAddrWidth)
Q_ENUM_NS(I2cReqestType)

}  // namespace I2cTypes

#endif  // I2CTYPES_H

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
    KHz40,
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
    SlaveNotify,
};

Q_ENUM_NS(I2cId)
Q_ENUM_NS(ClockFreq)
Q_ENUM_NS(MemAddrWidth)
Q_ENUM_NS(SlaveAddrWidth)
Q_ENUM_NS(I2cReqestType)

enum class MessageType {
    ConfigStatus = 0,
    MasterStatus,
    SlaveStatus,
    SlaveNotification,
    InvalidMessage,
};

enum class StatusCode {
    NotInit = 0,
    Success,
    BadRequest,
    NoSpace,
    SlaveNoAck,
    SlaveEarlyNack,
    InterfaceError,
};

}  // namespace I2cTypes

#endif  // I2CTYPES_H

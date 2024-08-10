#ifndef CTRLTYPES_H
#define CTRLTYPES_H

#include <QObject>

namespace CtrlTypes {

enum class MessageType {
    CtrlReqeust = 0,
    DeviceInfo,
    InvalidMessage,
};

}  // namespace CtrlTypes

#endif  // CTRLTYPES_H

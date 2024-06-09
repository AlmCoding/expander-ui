#ifndef USBCOMTYPES_H
#define USBCOMTYPES_H

extern "C" {
#include "TF_Config.h"
}

namespace driver::tf {

enum class TfMsgType : uint8_t {
    EchoMsg = 0,
    CtrlMsg,
    I2cMsg,
    SpiMsg,
    CanMsg,
    GpioMsg,
    PwmMsg,
    UartMsg,
    // Keep this at the end
    NumValues,
};

static_assert(static_cast<uint8_t>(TfMsgType::NumValues) <= TF_MAX_TYPE_LST,
              "Increase TF_MAX_TYPE_LST in TF_Config.h file.");

}  // namespace driver::tf

#endif /* USBCOMTYPES_H */

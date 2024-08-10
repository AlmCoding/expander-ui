#include "ctrlrequest.h"

CtrlRequest::CtrlRequest(bool get_device_info, bool reset_device, bool start_bootloader)
    : get_device_info_{ get_device_info }, reset_device_{ reset_device }, start_bootloader_{ start_bootloader } {}

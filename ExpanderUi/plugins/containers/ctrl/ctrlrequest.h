#ifndef CTRLREQUEST_H
#define CTRLREQUEST_H

#include "plugins/containers/ctrl/deviceinfo.h"

class CtrlRequest {
   public:
    CtrlRequest() = default;
    explicit CtrlRequest(bool get_device_info, bool reset_device, bool start_bootloader);

    void setRequestId(int request_id) { request_id_ = request_id; }
    void setGetDeviceInfo(bool get_device_info) { get_device_info_ = get_device_info; }
    void setResetDevice(bool reset_device) { reset_device_ = reset_device; }
    void setStartBootloader(bool start_bootloader) { start_bootloader_ = start_bootloader; }
    void setDeviceInfo(DeviceInfo& device_info) { device_info_ = device_info; }

    int getRequestId() const { return request_id_; }
    bool getGetDeviceInfo() const { return get_device_info_; }
    bool getResetDevice() const { return reset_device_; }
    bool getStartBootloader() const { return start_bootloader_; }
    DeviceInfo getDeviceInfo() const { return device_info_; }

   private:
    int request_id_ = -1;
    bool get_device_info_ = false;
    bool reset_device_ = false;
    bool start_bootloader_ = false;

    DeviceInfo device_info_;
};

#endif  // CTRLREQUEST_H

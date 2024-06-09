/*
 * FrameDriver.hpp
 *
 *  Created on: 24 May 2023
 *      Author: Alexander L.
 */

#ifndef DRIVER_TF_FRAMEDRIVER_HPP_
#define DRIVER_TF_FRAMEDRIVER_HPP_

#ifdef __cplusplus

#include "plugins/driver/common.hpp"
#include "plugins/driver/tf/tfMsgTypes.hpp"

extern "C" {
#include "TinyFrame.h"
}

namespace driver::tf {

typedef int32_t (*TxCallback)(uint8_t* data, size_t max_size);
typedef int32_t (*RxCallback)(const uint8_t* data, size_t size);

class FrameDriver {
   public:
    // Deleted copy constructor and assignment operator to enforce singleton
    FrameDriver(const FrameDriver&) = delete;
    FrameDriver& operator=(const FrameDriver&) = delete;

    static FrameDriver& getInstance() {
        static FrameDriver instance;
        return instance;
    }

    Status_t registerTxCallback(TfMsgType type, TxCallback callback);
    void callTxCallback(TfMsgType type, uint8_t* buffer, size_t max_size);

    Status_t registerRxCallback(TfMsgType type, RxCallback callback);
    void callRxCallback(TfMsgType type, const uint8_t* data, size_t size);

    void registerSendDataCallback(TxCallback callback);
    void sendData(const uint8_t* data, size_t size);     // Forward data to usb (upstream)
    void receiveData(const uint8_t* data, size_t size);  // Forward data to tf (downstream)

   private:
    FrameDriver();

    TinyFrame tf_;
    TxCallback send_callback_ = nullptr;
    TxCallback tx_callbacks_[static_cast<uint8_t>(TfMsgType::NumValues)] = {};
    RxCallback rx_callbacks_[static_cast<uint8_t>(TfMsgType::NumValues)] = {};
};

}  // namespace driver::tf
#endif

#endif /* DRIVER_TF_FRAMEDRIVER_HPP_ */

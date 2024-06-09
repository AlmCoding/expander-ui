#include "framedriver.h"
#include <QDebug>

namespace driver::tf {

TF_Result typeCallback(TinyFrame* tf, TF_Msg* msg);
TF_Result genericCallback(TinyFrame* tf, TF_Msg* msg);

FrameDriver::FrameDriver() : QObject{ nullptr } {
    TF_InitStatic(&tf_, TF_SLAVE);
    TF_AddGenericListener(&tf_, genericCallback);
}

void FrameDriver::forwardData(const QByteArray& data) { emit sendData(data); }

void FrameDriver::receiveData(const QByteArray& data) {
    TF_Accept(&tf_, reinterpret_cast<const uint8_t*>(data.data()), data.size());
}

bool FrameDriver::sendMessage(TfMsgType type, const QByteArray& data) {
    bool success = false;
    TF_Msg msg = {};

    msg.type = static_cast<TF_TYPE>(type);
    msg.data = reinterpret_cast<const uint8_t*>(data.data());
    msg.len = data.size();

    success = TF_Send(&tf_, &msg);
    return success;
}

TF_Result typeCallback(TinyFrame* /*tf*/, TF_Msg* msg) {
    qDebug("=>I msg (type: %d, size: %d)", msg->type, msg->len);
    auto& tf_driver = FrameDriver::getInstance();

    QByteArray data{ reinterpret_cast<const char*>(msg->data), msg->len };
    // tf_driver.callRxCallback(static_cast<TfMsgType>(msg->type), data);
    return TF_STAY;
}

TF_Result genericCallback(TinyFrame* /*tf*/, TF_Msg* msg) {
    if (msg->type < static_cast<TF_TYPE>(TfMsgType::NumValues)) {
        qDebug("No handler for msg type (%d) registerd!", msg->type);
    } else {
        qDebug("Unknown msg type: %d", msg->type);
    }
    return TF_STAY;
}

}  // namespace driver::tf

extern "C" {
void TF_WriteImpl(TinyFrame* /*tf*/, const uint8_t* buff, uint32_t len) {
    auto& tf_driver = driver::tf::FrameDriver::getInstance();
    QByteArray data{ reinterpret_cast<const char*>(buff), len };
    tf_driver.sendData(data);
}
}  // extern "C"

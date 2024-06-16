#include "framedriver.h"
#include <QDebug>

namespace driver::tf {

TF_Result genericCallback(TinyFrame* tf, TF_Msg* msg);

FrameDriver::FrameDriver() : QObject{ nullptr } {
    TF_InitStatic(&tf_, TF_SLAVE);
    TF_AddGenericListener(&tf_, genericCallback);
}

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

TF_Result genericCallback(TinyFrame* /*tf*/, TF_Msg* msg) {
    auto& tf_driver = driver::tf::FrameDriver::getInstance();
    QByteArray message{ reinterpret_cast<const char*>(msg->data), msg->len };

    switch (static_cast<TfMsgType>(msg->type)) {
        case TfMsgType::EchoMsg:
            tf_driver.echoMessage(message);
            break;
        case TfMsgType::I2cMsg:
            tf_driver.i2cMessage(message);
            break;
        default:
            qDebug("Unknown msg type: %d", msg->type);
            break;
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

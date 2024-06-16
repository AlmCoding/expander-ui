#ifndef FRAMEDRIVER_H
#define FRAMEDRIVER_H

#include <QByteArray>
#include <QObject>
#include "plugins/device/driver/tfmsgtypes.h"

extern "C" {
#include "TinyFrame.h"
}

namespace driver::tf {

class FrameDriver : public QObject {
    Q_OBJECT

   public:
    static FrameDriver& getInstance() {
        static FrameDriver instance;
        return instance;
    }

   public slots:
    bool sendMessage(TfMsgType type, const QByteArray& data);  // APP => TF (downstream)
    void receiveData(const QByteArray& data);                  // COM => TF (upstream)

   signals:
    void sendData(const QByteArray& data);  // TF => COM (downstream)

    void echoMessage(const QByteArray& data);  // Echo message received (TF => APP)
    void i2cMessage(const QByteArray& data);   // I2C message received (TF => APP)

   private:
    FrameDriver();

    TinyFrame tf_;
};

}  // namespace driver::tf

#endif  // FRAMEDRIVER_H

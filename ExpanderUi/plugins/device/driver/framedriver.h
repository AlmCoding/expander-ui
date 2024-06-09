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

    void forwardData(const QByteArray& data);  // Forward data to serial port (downstream)

   public slots:
    bool sendMessage(TfMsgType type, const QByteArray& data);  // Send message to tf (downstream)
    void receiveData(const QByteArray& data);                  // Forward data to tf (upstream)

   signals:
    void sendData(const QByteArray data);  // Send data to serial port (downstream)

   private:
    FrameDriver();

    TinyFrame tf_;
};

}  // namespace driver::tf

#endif  // FRAMEDRIVER_H

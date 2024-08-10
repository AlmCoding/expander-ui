#ifndef CTRLSERVICE_H
#define CTRLSERVICE_H

#include <QMap>
#include <QObject>
#include <QPair>
#include <QTimer>
#include "plugins/containers/ctrl/ctrlrequest.h"
#include "plugins/containers/ctrl/ctrltypes.h"
#include "plugins/containers/ctrl/deviceinfo.h"

class CtrlService : public QObject {
    Q_OBJECT
   public:
    explicit CtrlService(QObject* parent = nullptr);
    ~CtrlService();

    CtrlTypes::MessageType parseCtrlResponse(const QByteArray& message, CtrlRequest& request);

    bool createCtrlRequestMsg(CtrlRequest& request, QByteArray& message);

   private:
    constexpr static int TimeoutMs = 2000;
    constexpr static int TimeoutCheckPeriodMs = 25;
    struct TimeoutEntry {
        int request_id;
        qint64 timeout;
    };

    void checkTimeouts();
    bool handleDeviceInfo(DeviceInfo& device_info, CtrlRequest& request);

    int sequence_number_ = 0;
    int request_id_ = 0;

    QMap<int, CtrlRequest> request_map_;
    QList<TimeoutEntry> timeout_list_;

    QTimer timer_;
};

#endif  // CTRLSERVICE_H

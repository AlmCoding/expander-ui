#ifndef CTRLPROTOCOM_H
#define CTRLPROTOCOM_H

#include <QObject>
#include "plugins/containers/ctrl/ctrlrequest.h"
#include "plugins/containers/ctrl/ctrltypes.h"
#include "plugins/containers/ctrl/deviceinfo.h"
#include "proto_c/ctrl.pb.h"

class CtrlProtoCom : public QObject {
    Q_OBJECT
   public:
    explicit CtrlProtoCom(QObject* parent = nullptr);

    static CtrlTypes::MessageType decodeCtrlMsg(const QByteArray& message, DeviceInfo& device_info);

    static bool encodeCtrlRequest(const CtrlRequest& request, int sequence_number, QByteArray& message);

   private:
    static CtrlTypes::MessageType decodeDeviceInfo(const ctrl_proto_CtrlMsg& ctrl_msg, DeviceInfo& device_info);
};

#endif  // CTRLPROTOCOM_H

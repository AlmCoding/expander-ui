#ifndef I2CPROTOCOM_H
#define I2CPROTOCOM_H

#include <QObject>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2cconfigstatus.h"
#include "plugins/containers/i2cnotification.h"
#include "plugins/containers/i2crequest.h"
#include "plugins/containers/i2crequeststatus.h"
#include "proto_c/i2c.pb.h"

class I2cProtoCom : public QObject {
    Q_OBJECT
   public:
    explicit I2cProtoCom(QObject* parent = nullptr);

    static I2cTypes::MessageType decodeI2cMsg(const QByteArray& message, I2cConfigStatus& config_status,
                                              I2cRequestStatus& request_status, I2cNotification& notification);

    static bool encodeI2cConfig(const I2cConfig& config, int sequence_number, QByteArray& message);
    static bool encodeI2cMasterRequest(const I2cRequest& request, int sequence_number, QByteArray& message);
    static bool encodeI2cSlaveRequest(const I2cRequest& request, int sequence_number, QByteArray& message);

   private:
    static I2cTypes::MessageType decodeI2cConfigStatus(const i2c_proto_I2cMsg& i2c_msg, I2cConfigStatus& config_status);
    static I2cTypes::MessageType decodeI2cMasterStatus(const i2c_proto_I2cMsg& i2c_msg,
                                                       I2cRequestStatus& request_status);
    static I2cTypes::MessageType decodeI2cSlaveStatus(const i2c_proto_I2cMsg& i2c_msg,
                                                      I2cRequestStatus& request_status);
    static I2cTypes::MessageType decodeI2cSlaveNotification(const i2c_proto_I2cMsg& i2c_msg,
                                                            I2cNotification& notification);

    static bool hexStringToByteArray(const QString& hex_string, QByteArray& byte_array);
    static bool byteArrayToHexString(const QByteArray& byte_array, QString& hex_string);
};

#endif  // I2CPROTOCOM_H

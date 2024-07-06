#ifndef I2CPROTOCOM_H
#define I2CPROTOCOM_H

#include <QObject>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2cconfigstatus.h"
#include "plugins/containers/i2crequest.h"
#include "plugins/containers/i2crequeststatus.h"

class I2cProtoCom : public QObject {
    Q_OBJECT
   public:
    explicit I2cProtoCom(QObject* parent = nullptr);

    static bool decodeI2cMsg(const QByteArray& message, I2cConfigStatus** config_status,
                             I2cRequestStatus** request_status);

    static bool encodeI2cConfig(const I2cConfig& config, int sequence_number, QByteArray& message);
    static bool encodeI2cRequest(const I2cRequest& request, int sequence_number, QByteArray& message);

   private:
    static bool hexStringToByteArray(const QString& hex_string, QByteArray& byte_array);
    static bool byteArrayToHexString(const QByteArray& byte_array, QString& hex_string);
};

#endif  // I2CPROTOCOM_H

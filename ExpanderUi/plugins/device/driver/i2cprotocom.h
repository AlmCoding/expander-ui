#ifndef I2CPROTOCOM_H
#define I2CPROTOCOM_H

#include <QObject>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2crequest.h"

class I2cProtoCom : public QObject {
    Q_OBJECT
   public:
    explicit I2cProtoCom(QObject* parent = nullptr);

    bool encodeI2cConfig(const I2cConfig& config, QByteArray& message);
    bool encodeI2cRequest(const I2cRequest& request, QByteArray& message);

   private:
    bool hexStringToByteArray(const QString& hex_string, QByteArray& byte_array);

    int sequence_number_ = 0;
    int request_id_ = 0;
};

#endif  // I2CPROTOCOM_H

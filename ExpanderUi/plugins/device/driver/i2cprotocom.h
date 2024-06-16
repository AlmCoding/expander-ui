#ifndef I2CPROTOCOM_H
#define I2CPROTOCOM_H

#include <QObject>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2crequest.h"

class I2cProtoCom : public QObject {
    Q_OBJECT
   public:
    explicit I2cProtoCom(QObject* parent = nullptr);

    static bool encodeI2cConfig(const I2cConfig& config, QByteArray& message);
    static bool encodeI2cRequest(const I2cRequest& request, QByteArray& message);

   signals:
};

#endif  // I2CPROTOCOM_H

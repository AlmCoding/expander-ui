#ifndef I2CSERVICE_H
#define I2CSERVICE_H

#include <QMap>
#include <QObject>
#include <QPair>
#include <QTimer>
#include "plugins/containers/i2c/i2cconfig.h"
#include "plugins/containers/i2c/i2cconfigstatus.h"
#include "plugins/containers/i2c/i2cnotification.h"
#include "plugins/containers/i2c/i2crequest.h"
#include "plugins/containers/i2c/i2crequeststatus.h"
#include "plugins/containers/i2c/i2ctypes.h"

class I2cService : public QObject {
    Q_OBJECT

   public:
    explicit I2cService(QObject* parent = nullptr);
    ~I2cService();

    I2cTypes::MessageType parseI2cResponse(const QByteArray& message, I2cConfig& config, I2cRequest& request,
                                           I2cNotification& notification);

    bool createI2cConfigMsg(I2cConfig& config, QByteArray& message);
    bool createI2cRequestMsg(I2cRequest& request, QByteArray& message);

   signals:
    void statusMessage(QString message);

   private:
    constexpr static int TimeoutMs = 2000;
    constexpr static int TimeoutCheckPeriodMs = 25;

    struct TimeoutEntry {
        int request_id;
        qint64 timeout;
    };

    void checkTimeouts();
    bool handleConfigStatus(I2cConfigStatus& config_status, I2cConfig& config);
    bool handleRequestStatus(I2cRequestStatus& request_status, I2cRequest& request);

    int sequence_number0_ = 0;
    int sequence_number1_ = 0;
    int request_id_ = 0;

    I2cConfig config0_;
    I2cConfig config1_;
    QMap<int, I2cConfig> config_map_;
    QMap<int, I2cRequest> request_map_;
    QList<TimeoutEntry> timeout_list_;

    QTimer timer_;
};

#endif  // I2CSERVICE_H

#ifndef I2CSERVICE_H
#define I2CSERVICE_H

#include <QMap>
#include <QObject>
#include <QPair>
#include <QTimer>
#include "plugins/containers/i2cconfig.h"
#include "plugins/containers/i2cconfigstatus.h"
#include "plugins/containers/i2crequest.h"
#include "plugins/containers/i2crequeststatus.h"

constexpr int TimeoutMs = 1000;
constexpr int TimeoutCheckPeriodMs = 25;

class I2cService : public QObject {
    Q_OBJECT
   public:
    explicit I2cService(QObject* parent = nullptr);
    ~I2cService();

    I2cTypes::MessageType parseI2cResponse(const QByteArray& message, I2cConfig& config, I2cRequest& request);

    bool createI2cConfigMsg(I2cConfig& config, QByteArray& message);
    bool createI2cRequestMsg(I2cRequest& request, QByteArray& message);

   private:
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

    QMap<int, I2cConfig> config_map_;
    QMap<int, I2cRequest> request_map_;
    QList<TimeoutEntry> timeout_list_;

    QTimer timer_;
};

#endif  // I2CSERVICE_H

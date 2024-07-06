#include "i2cservice.h"
#include <QDateTime>
#include <QDebug>
#include "plugins/containers/i2cconfigstatus.h"
#include "plugins/device/driver/i2cprotocom.h"

I2cService::I2cService(QObject* parent) : QObject{ parent } {
    timer_.setInterval(TimeoutCheckPeriodMs);
    connect(&timer_, &QTimer::timeout, this, &I2cService::checkTimeouts);
    timer_.start();
}

I2cService::~I2cService() { timer_.stop(); }

bool I2cService::parseI2cResponse(const QByteArray& message) {
    I2cConfigStatus* config_status = nullptr;

    if (I2cProtoCom::decodeI2cMsg(message, &config_status) == false) {
        qDebug() << "Failed to decode I2C message!";
        delete config_status;
        return false;
    }

    if (config_status != nullptr) {
        if (config_map_.contains(config_status->getRequestId())) {
            config_map_.remove(config_status->getRequestId());
            for (auto iter = timeout_list_.begin(); iter != timeout_list_.end(); ++iter) {
                if (iter->request_id == config_status->getRequestId()) {
                    timeout_list_.erase(iter);
                    break;
                }
            }
            if (config_status->getStatusCode() == I2cConfigStatus::StatusCode::Ok) {
                qDebug() << "I2C config successful!";
            } else {
                qDebug() << "I2C config failed!";
            }
        } else {
            qDebug() << "Received I2C config response with unknown request ID!";
        }
    }

    delete config_status;
    return true;
}

bool I2cService::createI2cConfigMsg(I2cConfig& config, QByteArray& message) {
    int sequence_number = 0;
    if (config.i2c_id == I2cConfigTypes::I2cId::I2c0) {
        sequence_number = sequence_number0_++;
    } else if (config.i2c_id == I2cConfigTypes::I2cId::I2c1) {
        sequence_number = sequence_number1_++;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }
    config.request_id = request_id_++;

    if (I2cProtoCom::encodeI2cConfig(config, sequence_number, message) == false) {
        qDebug() << "Failed to create I2C config message!";
        return false;
    }

    config_map_.insert(config.request_id, config);
    timeout_list_.append({ config.request_id, QDateTime::currentMSecsSinceEpoch() + TimeoutMs });
    return true;
}

bool I2cService::createI2cRequestMsg(I2cRequest& request, QByteArray& message) {
    int sequence_number = 0;
    auto i2c_id = request.getI2cId();
    if (i2c_id == I2cConfigTypes::I2cId::I2c0) {
        sequence_number = sequence_number0_++;
    } else if (i2c_id == I2cConfigTypes::I2cId::I2c1) {
        sequence_number = sequence_number1_++;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }
    request.setRequestId(request_id_++);

    if (I2cProtoCom::encodeI2cRequest(request, sequence_number, message) == false) {
        qDebug() << "Failed to create I2C request message!";
        return false;
    }

    request_map_.insert(request.getRequestId(), request);
    timeout_list_.append({ request.getRequestId(), QDateTime::currentMSecsSinceEpoch() + TimeoutMs });
    return true;
}

void I2cService::checkTimeouts() {
    auto current_time = QDateTime::currentMSecsSinceEpoch();
    for (auto iter = timeout_list_.begin(); iter != timeout_list_.end();) {
        if (current_time > iter->timeout) {
            if (config_map_.contains(iter->request_id)) {
                config_map_.remove(iter->request_id);
            } else if (request_map_.contains(iter->request_id)) {
                request_map_.remove(iter->request_id);
            }
            qDebug() << "Timeout for request request_id: " << iter->request_id;
            iter = timeout_list_.erase(iter);
            // TODO: emit timeout signal
        } else {
            ++iter;
        }
    }
}

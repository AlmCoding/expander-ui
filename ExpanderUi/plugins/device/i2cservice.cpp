#include "i2cservice.h"
#include <QDateTime>
#include <QDebug>
#include "plugins/containers/i2ctypes.h"
#include "plugins/device/driver/i2cprotocom.h"

I2cService::I2cService(QObject* parent) : QObject{ parent } {
    timer_.setInterval(TimeoutCheckPeriodMs);
    connect(&timer_, &QTimer::timeout, this, &I2cService::checkTimeouts);
    timer_.start();
}

I2cService::~I2cService() { timer_.stop(); }

I2cTypes::MessageType I2cService::parseI2cResponse(const QByteArray& message, I2cConfig& config, I2cRequest& request,
                                                   I2cNotification& notification) {
    I2cConfigStatus config_status;
    I2cRequestStatus request_status;
    I2cTypes::MessageType msg_type = I2cProtoCom::decodeI2cMsg(message, config_status, request_status, notification);

    if (msg_type == I2cTypes::MessageType::ConfigStatus) {
        if (handleConfigStatus(config_status, config) == true) {
            return I2cTypes::MessageType::ConfigStatus;
        }

    } else if (msg_type == I2cTypes::MessageType::MasterStatus) {
        if (handleRequestStatus(request_status, request) == true) {
            return I2cTypes::MessageType::MasterStatus;
        }

    } else if (msg_type == I2cTypes::MessageType::SlaveStatus) {
        if (handleRequestStatus(request_status, request) == true) {
            return I2cTypes::MessageType::SlaveStatus;
        }

    } else if (msg_type == I2cTypes::MessageType::SlaveNotification) {
        return I2cTypes::MessageType::SlaveNotification;

    } else {
        qDebug() << "Failed to decode I2C message!";
    }

    return I2cTypes::MessageType::InvalidMessage;
}

bool I2cService::handleConfigStatus(I2cConfigStatus& config_status, I2cConfig& config) {
    int request_id = config_status.getRequestId();

    if (config_map_.contains(request_id) == true) {
        // Remove config from map
        config = config_map_.take(request_id);

        // Remove config from timeout list
        for (auto iter = timeout_list_.begin(); iter != timeout_list_.end(); ++iter) {
            if (iter->request_id == request_id) {
                timeout_list_.erase(iter);
                break;
            }
        }

        // Insert status into config
        config.status = config_status;
        return true;

    } else {
        qDebug() << "Received I2C config response with unknown request ID!";
        return false;
    }
}

bool I2cService::handleRequestStatus(I2cRequestStatus& request_status, I2cRequest& request) {
    int request_id = request_status.getRequestId();

    if (request_map_.contains(request_id) == true) {
        // Remove request from map
        request = request_map_.take(request_id);

        // Remove request from timeout list
        for (auto iter = timeout_list_.begin(); iter != timeout_list_.end(); ++iter) {
            if (iter->request_id == request_id) {
                timeout_list_.erase(iter);
                break;
            }
        }

        // Insert status into request
        request.setStatus(request_status);
        return true;

    } else {
        qDebug() << "Received I2C request response with unknown request ID!";
        return false;
    }
}

bool I2cService::createI2cConfigMsg(I2cConfig& config, QByteArray& message) {
    int sequence_number = 0;
    if (config.i2c_id == I2cTypes::I2cId::I2c0) {
        sequence_number = sequence_number0_++;
    } else if (config.i2c_id == I2cTypes::I2cId::I2c1) {
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
    if (i2c_id == I2cTypes::I2cId::I2c0) {
        sequence_number = sequence_number0_++;
    } else if (i2c_id == I2cTypes::I2cId::I2c1) {
        sequence_number = sequence_number1_++;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }
    request.setRequestId(request_id_++);

    if (request.getType() == I2cTypes::I2cReqestType::MasterAction) {
        if (I2cProtoCom::encodeI2cMasterRequest(request, sequence_number, message) == false) {
            qDebug() << "Failed to create I2cMaster request message!";
            return false;
        }
    } else if (request.getType() == I2cTypes::I2cReqestType::SlaveConfig) {
        if (I2cProtoCom::encodeI2cSlaveRequest(request, sequence_number, message) == false) {
            qDebug() << "Failed to create I2cSlave request message!";
            return false;
        }
    } else {
        qDebug("Invalid I2cRequestType!");
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
            qDebug() << "Timeout for request with request_id:" << iter->request_id;
            iter = timeout_list_.erase(iter);
            // TODO: emit timeout signal
        } else {
            ++iter;
        }
    }
}

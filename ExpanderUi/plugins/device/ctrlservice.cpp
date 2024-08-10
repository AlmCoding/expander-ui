#include "ctrlservice.h"
#include <QDateTime>
#include <QDebug>
#include "plugins/device/driver/ctrlprotocom.h"

CtrlService::CtrlService(QObject* parent) : QObject{ parent } {}

CtrlService::~CtrlService() { timer_.stop(); }

CtrlTypes::MessageType CtrlService::parseCtrlResponse(const QByteArray& message, CtrlRequest& request) {
    DeviceInfo device_info;
    CtrlTypes::MessageType msg_type = CtrlProtoCom::decodeCtrlMsg(message, device_info);

    if (msg_type == CtrlTypes::MessageType::DeviceInfo) {
        if (handleDeviceInfo(device_info, request) == true) {
            return CtrlTypes::MessageType::DeviceInfo;
        }
    } else {
        qDebug() << "Failed to decode control message!";
    }

    return CtrlTypes::MessageType::InvalidMessage;
}

bool CtrlService::handleDeviceInfo(DeviceInfo& device_info, CtrlRequest& request) {
    int request_id = device_info.getRequestId();

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

        // Insert device info into request
        request.setDeviceInfo(device_info);
        return true;

    } else {
        qDebug() << "Received CTRL request response with unknown request_id: " << request_id;
        return false;
    }
}

bool CtrlService::createCtrlRequestMsg(CtrlRequest& request, QByteArray& message) {
    int sequence_number = sequence_number_++;
    request.setRequestId(request_id_++);

    if (CtrlProtoCom::encodeCtrlRequest(request, sequence_number, message) == false) {
        qDebug() << "Failed to encode CTRL request message!";
        return false;
    }

    request_map_.insert(request.getRequestId(), request);
    timeout_list_.append({ request.getRequestId(), QDateTime::currentMSecsSinceEpoch() + TimeoutMs });
    return true;
}

void CtrlService::checkTimeouts() {
    qint64 current_time = QDateTime::currentMSecsSinceEpoch();

    for (auto iter = timeout_list_.begin(); iter != timeout_list_.end();) {
        if (current_time >= iter->timeout) {
            int request_id = iter->request_id;

            if (request_map_.contains(request_id) == true) {
                request_map_.remove(request_id);
            } else {
                assert(false);
            }
            qDebug() << "Timeout for request with request_id: " << request_id;
            iter = timeout_list_.erase(iter);
            // TODO: Emit timeout signal
        } else {
            ++iter;
        }
    }
}

#include "ctrlprotocom.h"
#include <QDebug>
#include "magic_enum.hpp"
#include "pb_common.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "proto_c/ctrl.pb.h"

CtrlProtoCom::CtrlProtoCom(QObject* parent) : QObject{ parent } {}

CtrlTypes::MessageType CtrlProtoCom::decodeCtrlMsg(const QByteArray& message, DeviceInfo& device_info) {
    /* Allocate space for the decoded message. */
    ctrl_proto_CtrlMsg ctrl_msg = ctrl_proto_CtrlMsg_init_zero;
    /* Create a stream that reads from the buffer. */
    pb_istream_t stream = pb_istream_from_buffer(reinterpret_cast<const uint8_t*>(message.data()), message.size());

    /* Now we are ready to decode the message. */
    if (pb_decode(&stream, ctrl_proto_CtrlMsg_fields, &ctrl_msg) == false) {
        qDebug("Failed to decode CTRL message!");
        return CtrlTypes::MessageType::InvalidMessage;
    }

    if (ctrl_msg.which_msg == ctrl_proto_CtrlMsg_device_info_tag) {
        return decodeDeviceInfo(ctrl_msg, device_info);

    } else {
        qDebug("Invalid message type!");
        return CtrlTypes::MessageType::InvalidMessage;
    }
}

CtrlTypes::MessageType CtrlProtoCom::decodeDeviceInfo(const ctrl_proto_CtrlMsg& ctrl_msg, DeviceInfo& device_info) {
    device_info.setDeviceType(ctrl_msg.msg.device_info.device_type);
    device_info.setHardwareVersion(ctrl_msg.msg.device_info.hardware_version);

    device_info.setFirmwareVersionMajor(ctrl_msg.msg.device_info.firmware_version_major);
    device_info.setFirmwareVersionMinor(ctrl_msg.msg.device_info.firmware_version_minor);
    device_info.setFirmwareVersionPatch(ctrl_msg.msg.device_info.firmware_version_patch);

    QString git_hash{ ctrl_msg.msg.device_info.git_hash };
    device_info.setGitHash(git_hash);

    qDebug("Received CTRL device-info response!");
    qDebug("  Device type: %d", device_info.getDeviceType());
    qDebug("  Hardware version: %d", device_info.getHardwareVersion());
    qDebug("  Firmware version: %d.%d.%d", device_info.getFirmwareVersionMajor(), device_info.getFirmwareVersionMinor(),
           device_info.getFirmwareVersionPatch());
    qDebug("  Git hash: %s", device_info.getGitHash().toStdString().c_str());
    return CtrlTypes::MessageType::DeviceInfo;
}

bool CtrlProtoCom::encodeCtrlRequest(const CtrlRequest& request, int sequence_number, QByteArray& message) {
    bool success = false;
    /* Allocate space for the decoded message. */
    ctrl_proto_CtrlMsg ctrl_msg = ctrl_proto_CtrlMsg_init_zero;
    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(reinterpret_cast<uint8_t*>(message.data()), message.capacity());

    ctrl_msg.sequence_number = sequence_number;
    ctrl_msg.which_msg = ctrl_proto_CtrlMsg_ctrl_request_tag;

    ctrl_msg.msg.ctrl_request.get_device_info = request.getGetDeviceInfo();
    ctrl_msg.msg.ctrl_request.reset_system = request.getResetDevice();
    ctrl_msg.msg.ctrl_request.start_bootloader = request.getStartBootloader();

    /* Now we are ready to encode the message! */
    if (pb_encode(&stream, ctrl_proto_CtrlMsg_fields, &ctrl_msg) == false) {
        qDebug("Failed to encode message!");
        message.clear();
        return false;
    }

    message.resize(stream.bytes_written);
    return true;
}

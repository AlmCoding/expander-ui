#include "i2cprotocom.h"
#include <QDebug>
#include "magic_enum.hpp"
#include "pb_common.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "plugins/containers/i2ctypes.h"
#include "proto_c/i2c.pb.h"

I2cProtoCom::I2cProtoCom(QObject* parent) : QObject{ parent } {}

I2cTypes::MessageType I2cProtoCom::decodeI2cMsg(const QByteArray& message, I2cConfigStatus& config_status,
                                                I2cRequestStatus& request_status, I2cNotification& notification) {
    /* Allocate space for the decoded message. */
    i2c_proto_I2cMsg i2c_msg = i2c_proto_I2cMsg_init_zero;
    /* Create a stream that reads from the buffer. */
    pb_istream_t stream = pb_istream_from_buffer(reinterpret_cast<const uint8_t*>(message.data()), message.size());

    /* Now we are ready to decode the message. */
    if (pb_decode(&stream, i2c_proto_I2cMsg_fields, &i2c_msg) == false) {
        qDebug("Failed to decode I2C message!");
        return I2cTypes::MessageType::InvalidMessage;
    }

    if (i2c_msg.which_msg == i2c_proto_I2cMsg_config_status_tag) {
        return decodeI2cConfigStatus(i2c_msg, config_status);

    } else if (i2c_msg.which_msg == i2c_proto_I2cMsg_master_status_tag) {
        return decodeI2cMasterStatus(i2c_msg, request_status);

    } else if (i2c_msg.which_msg == i2c_proto_I2cMsg_slave_status_tag) {
        return decodeI2cSlaveStatus(i2c_msg, request_status);

    } else if (i2c_msg.which_msg == i2c_proto_I2cMsg_slave_notification_tag) {
        return decodeI2cSlaveNotification(i2c_msg, notification);

    } else {
        qDebug("Invalid message type!");
        return I2cTypes::MessageType::InvalidMessage;
    }
}

I2cTypes::MessageType I2cProtoCom::decodeI2cConfigStatus(const i2c_proto_I2cMsg& i2c_msg,
                                                         I2cConfigStatus& config_status) {
    int request_id = i2c_msg.msg.config_status.request_id;
    I2cConfigStatus::StatusCode status_code =
        static_cast<I2cConfigStatus::StatusCode>(i2c_msg.msg.config_status.status_code);

    config_status.setRequestId(request_id);
    config_status.setStatusCode(status_code);

    qDebug("Received I2C config response!");
    qDebug("  Request ID: %d", config_status.getRequestId());
    qDebug("  Status: %s", magic_enum::enum_name(config_status.getStatusCode()).data());
    return I2cTypes::MessageType::ConfigStatus;
}

I2cTypes::MessageType I2cProtoCom::decodeI2cMasterStatus(const i2c_proto_I2cMsg& i2c_msg,
                                                         I2cRequestStatus& request_status) {
    int request_id = i2c_msg.msg.master_status.request_id;
    I2cTypes::StatusCode status_code = static_cast<I2cTypes::StatusCode>(i2c_msg.msg.master_status.status_code);
    QByteArray read_data{ reinterpret_cast<const char*>(i2c_msg.msg.master_status.read_data.bytes),
                          i2c_msg.msg.master_status.read_data.size };

    QString read_data_hex;
    if (byteArrayToHexString(read_data, read_data_hex) == false) {
        qDebug("Failed to convert read data to hex string!");
        return I2cTypes::MessageType::InvalidMessage;
    }

    request_status.setRequestId(request_id);
    request_status.setStatusCode(status_code);
    request_status.setReadData(read_data_hex);

    qDebug("Received I2C master response!");
    qDebug("  Request ID: %d", request_status.getRequestId());
    qDebug("  Status: %s", magic_enum::enum_name(request_status.getStatusCode()).data());
    qDebug("  Read data: %s", qPrintable(request_status.getReadData()));
    return I2cTypes::MessageType::MasterStatus;
}

I2cTypes::MessageType I2cProtoCom::decodeI2cSlaveStatus(const i2c_proto_I2cMsg& i2c_msg,
                                                        I2cRequestStatus& request_status) {
    int request_id = i2c_msg.msg.slave_status.request_id;
    I2cTypes::StatusCode status_code = static_cast<I2cTypes::StatusCode>(i2c_msg.msg.slave_status.status_code);
    QByteArray read_data{ reinterpret_cast<const char*>(i2c_msg.msg.slave_status.read_data.bytes),
                          i2c_msg.msg.slave_status.read_data.size };

    QString read_data_hex;
    if (byteArrayToHexString(read_data, read_data_hex) == false) {
        qDebug("Failed to convert read data to hex string!");
        return I2cTypes::MessageType::InvalidMessage;
    }

    request_status.setRequestId(request_id);
    request_status.setStatusCode(status_code);
    request_status.setReadData(read_data_hex);

    qDebug("Received I2C slave response!");
    qDebug("  Request ID: %d", request_id);
    qDebug("  Status: %s", magic_enum::enum_name(status_code).data());
    qDebug("  Read data: %s", qPrintable(read_data_hex));
    return I2cTypes::MessageType::SlaveStatus;
}

I2cTypes::MessageType I2cProtoCom::decodeI2cSlaveNotification(const i2c_proto_I2cMsg& i2c_msg,
                                                              I2cNotification& notification) {
    int access_id = i2c_msg.msg.slave_notification.access_id;
    I2cTypes::StatusCode status_code = static_cast<I2cTypes::StatusCode>(i2c_msg.msg.slave_notification.status_code);
    QByteArray write_data{ reinterpret_cast<const char*>(i2c_msg.msg.slave_notification.write_data.bytes),
                           i2c_msg.msg.slave_notification.write_data.size };

    QString write_data_hex;
    if (byteArrayToHexString(write_data, write_data_hex) == false) {
        qDebug("Failed to convert write data to hex string!");
        return I2cTypes::MessageType::InvalidMessage;
    }

    /*
    QString write_addr = QString("0x%1").arg(i2c_msg.msg.slave_notification.write_addr, 4, 16, QChar('0'));

    notification.setAccessId(access_id);
    notification.setStatusCode(status_code);
    notification.setWriteAddr(write_addr);
    notification.setWriteData(write_data_hex);
    notification.setReadAddr(read_addr);
    notification.setReadSize(read_size);

    qDebug("Received I2C slave notification!");
    qDebug("  Access ID: %d", access_id);
    qDebug("  Status: %s", magic_enum::enum_name(status_code).data());

    qDebug("  Write addr: 0x%04X", write_addr);
    qDebug("  Write data: %s", qPrintable(write_data_hex);
    qDebug("  Read addr: 0x%04X", read_addr);
    qDebug("  Read size: %d", read_size);
    */

    return I2cTypes::MessageType::SlaveNotification;
}

bool I2cProtoCom::encodeI2cConfig(const I2cConfig& config, int sequence_number, QByteArray& message) {
    bool success = false;
    /* Allocate space for the decoded message. */
    i2c_proto_I2cMsg i2c_msg = i2c_proto_I2cMsg_init_zero;
    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(reinterpret_cast<uint8_t*>(message.data()), message.capacity());

    if (config.i2c_id == I2cTypes::I2cId::I2c0) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C0;
    } else if (config.i2c_id == I2cTypes::I2cId::I2c1) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C1;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }

    i2c_msg.sequence_number = sequence_number;
    i2c_msg.which_msg = i2c_proto_I2cMsg_config_request_tag;
    i2c_msg.msg.config_request.request_id = config.request_id;

    QString slave_addr{ config.slave_addr };
    if (slave_addr.startsWith("0x", Qt::CaseInsensitive)) {
        slave_addr = slave_addr.mid(2);
    }
    bool ok = false;
    i2c_msg.msg.config_request.slave_addr = slave_addr.toUInt(&ok, 16);
    if (ok == false) {
        qDebug("Invalid slave address!");
        return false;
    }

    switch (config.clock_freq) {
        case I2cTypes::ClockFreq::KHz10:
            i2c_msg.msg.config_request.clock_freq = 10e3;
            break;
        case I2cTypes::ClockFreq::KHz100:
            i2c_msg.msg.config_request.clock_freq = 100e3;
            break;
        case I2cTypes::ClockFreq::KHz400:
            i2c_msg.msg.config_request.clock_freq = 400e3;
            break;
        case I2cTypes::ClockFreq::KHz1000:
            i2c_msg.msg.config_request.clock_freq = 1000e3;
            break;
        default:
            qDebug("Invalid clock frequency!");
            return false;
    }

    i2c_msg.msg.config_request.slave_addr_width = (config.slave_addr_width == I2cTypes::SlaveAddrWidth::SevenBit)
                                                      ? i2c_proto_AddressWidth_Bits7
                                                      : i2c_proto_AddressWidth_Bits10;
    i2c_msg.msg.config_request.mem_addr_width = (config.mem_addr_width == I2cTypes::MemAddrWidth::OneByte)
                                                    ? i2c_proto_AddressWidth_Bits8
                                                    : i2c_proto_AddressWidth_Bits16;
    i2c_msg.msg.config_request.pullups_enabled = true;

    /* Now we are ready to encode the message! */
    if (pb_encode(&stream, i2c_proto_I2cMsg_fields, &i2c_msg) == false) {
        qDebug("Failed to encode message!");
        message.clear();
        return false;
    }

    message.resize(stream.bytes_written);
    return true;
}

bool I2cProtoCom::encodeI2cMasterRequest(const I2cRequest& request, int sequence_number, QByteArray& message) {
    bool success = false;
    /* Allocate space for the decoded message. */
    i2c_proto_I2cMsg i2c_msg = i2c_proto_I2cMsg_init_zero;
    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(reinterpret_cast<uint8_t*>(message.data()), message.capacity());

    auto i2c_id = request.getI2cId();
    if (i2c_id == I2cTypes::I2cId::I2c0) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C0;
    } else if (i2c_id == I2cTypes::I2cId::I2c1) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C1;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }

    i2c_msg.sequence_number = sequence_number;
    i2c_msg.which_msg = i2c_proto_I2cMsg_master_request_tag;
    i2c_msg.msg.master_request.request_id = request.getRequestId();

    QString slave_addr{ request.getSlaveAddr() };
    if (slave_addr.startsWith("0x", Qt::CaseInsensitive)) {
        slave_addr = slave_addr.mid(2);
    }
    bool ok = false;
    i2c_msg.msg.master_request.slave_addr = slave_addr.toUInt(&ok, 16);
    if (ok == false) {
        qDebug("Invalid slave address!");
        return false;
    }

    QByteArray write_data;
    if (hexStringToByteArray(request.getWriteData(), write_data) == false) {
        qDebug("Invalid write data!");
        return false;
    }
    i2c_msg.msg.master_request.write_data.size = write_data.size();
    std::memcpy(i2c_msg.msg.master_request.write_data.bytes, write_data.data(), write_data.size());

    i2c_msg.msg.master_request.read_size = request.getReadSize().toUInt();
    i2c_msg.msg.master_request.sequence_id = 0;
    i2c_msg.msg.master_request.sequence_idx = 0;

    /* Now we are ready to encode the message! */
    if (pb_encode(&stream, i2c_proto_I2cMsg_fields, &i2c_msg) == false) {
        qDebug("Failed to encode message!");
        message.clear();
        return false;
    }

    message.resize(stream.bytes_written);
    return true;
}

bool I2cProtoCom::encodeI2cSlaveRequest(const I2cRequest& request, int sequence_number, QByteArray& message) {
    bool success = false;
    /* Allocate space for the decoded message. */
    i2c_proto_I2cMsg i2c_msg = i2c_proto_I2cMsg_init_zero;
    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(reinterpret_cast<uint8_t*>(message.data()), message.capacity());

    auto i2c_id = request.getI2cId();
    if (i2c_id == I2cTypes::I2cId::I2c0) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C0;
    } else if (i2c_id == I2cTypes::I2cId::I2c1) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C1;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }

    i2c_msg.sequence_number = sequence_number;
    i2c_msg.which_msg = i2c_proto_I2cMsg_slave_request_tag;
    i2c_msg.msg.slave_request.request_id = request.getRequestId();

    QByteArray write_data;
    if (hexStringToByteArray(request.getWriteData(), write_data) == false) {
        qDebug("Invalid write data!");
        return false;
    }
    QByteArray addr_bytes = write_data.left(2);
    write_data.remove(0, 2);

    i2c_msg.msg.slave_request.write_data.size = write_data.size();
    std::memcpy(i2c_msg.msg.slave_request.write_data.bytes, write_data.data(), write_data.size());

    i2c_msg.msg.slave_request.read_size = request.getReadSize().toInt();

    uint8_t byte1 = static_cast<uint8_t>(addr_bytes[0]);
    uint8_t byte2 = static_cast<uint8_t>(addr_bytes[1]);
    int address = (byte1 << 8) | byte2;
    i2c_msg.msg.slave_request.write_addr = address;
    i2c_msg.msg.slave_request.read_addr = address;

    /* Now we are ready to encode the message! */
    if (pb_encode(&stream, i2c_proto_I2cMsg_fields, &i2c_msg) == false) {
        qDebug("Failed to encode message!");
        message.clear();
        return false;
    }

    message.resize(stream.bytes_written);
    return true;
}

bool I2cProtoCom::hexStringToByteArray(const QString& hex_string, QByteArray& byte_array) {
    QString hex{ hex_string };
    hex.remove(' ');

    byte_array.clear();
    byte_array.reserve(hex.length() / 2 + 1);

    bool ok = false;
    for (int i = 0; i < hex.length(); i += 2) {
        byte_array.append(hex.mid(i, 2).toUInt(&ok, 16));
        if (ok == false) {
            return false;
        }
    }
    return true;
}

bool I2cProtoCom::byteArrayToHexString(const QByteArray& byte_array, QString& hex_string) {
    hex_string.clear();
    hex_string.reserve(byte_array.length() * 2 + 1);

    for (int i = 0; i < byte_array.length(); i++) {
        hex_string.append(QString("%1").arg(byte_array.at(i), 2, 16, QChar('0')));
        hex_string.append(' ');
    }
    return true;
}

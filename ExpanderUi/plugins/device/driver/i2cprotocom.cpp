#include "i2cprotocom.h"
#include <QDebug>
#include "pb_common.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "proto_c/i2c.pb.h"

I2cProtoCom::I2cProtoCom(QObject* parent) : QObject{ parent } {}

bool I2cProtoCom::encodeI2cConfig(const I2cConfig& config, QByteArray& message) {
    bool success = false;
    /* Allocate space for the decoded message. */
    i2c_proto_I2cMsg i2c_msg = i2c_proto_I2cMsg_init_zero;
    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(reinterpret_cast<uint8_t*>(message.data()), message.capacity());

    if (config.i2c_id == I2cConfigTypes::I2cId::I2c0) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C0;
    } else if (config.i2c_id == I2cConfigTypes::I2cId::I2c1) {
        i2c_msg.i2c_id = i2c_proto_I2cId::i2c_proto_I2cId_I2C1;
    } else {
        qDebug("Invalid I2cId!");
        return false;
    }

    i2c_msg.sequence_number = 0;
    i2c_msg.which_msg = i2c_proto_I2cMsg_cfg_tag;

    switch (config.clock_freq) {
        case I2cConfigTypes::ClockFreq::KHz10:
            i2c_msg.msg.cfg.clock_freq = 10e3;
            break;
        case I2cConfigTypes::ClockFreq::KHz100:
            i2c_msg.msg.cfg.clock_freq = 100e3;
            break;
        case I2cConfigTypes::ClockFreq::KHz400:
            i2c_msg.msg.cfg.clock_freq = 400e3;
            break;
        case I2cConfigTypes::ClockFreq::KHz1000:
            i2c_msg.msg.cfg.clock_freq = 1000e3;
            break;
        default:
            qDebug("Invalid clock frequency!");
            return false;
    }

    QString slave_addr{config.slave_addr};
    if (config.slave_addr.startsWith("0x", Qt::CaseInsensitive)) {
        slave_addr = slave_addr.mid(2);
    }
    bool ok = false;
    i2c_msg.msg.cfg.slave_addr = slave_addr.toUInt(&ok, 16);
    if (ok == false) {
        qDebug("Invalid slave address!");
        return false;
    }

    i2c_msg.msg.cfg.slave_addr_width = (config.slave_addr_width == I2cConfigTypes::SlaveAddrWidth::SevenBit)
                                       ? i2c_proto_AddressWidth_Bits7
                                       : i2c_proto_AddressWidth_Bits10;
    i2c_msg.msg.cfg.mem_addr_width = (config.mem_addr_width == I2cConfigTypes::MemAddrWidth::OneByte)
                                     ? i2c_proto_AddressWidth_Bits8
                                     : i2c_proto_AddressWidth_Bits16;
    i2c_msg.msg.cfg.pullups_enabled = true;

    /* Now we are ready to encode the message! */
    if (pb_encode(&stream, i2c_proto_I2cMsg_fields, &i2c_msg) == false) {
        qDebug("Failed to encode message!");
        message.clear();
        return false;
    }

    message.resize(stream.bytes_written);
    return true;
}

bool I2cProtoCom::encodeI2cRequest(const I2cRequest& request, QByteArray& message) { return true; }

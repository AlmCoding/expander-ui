#include "i2crequest.h"

I2cRequest::I2cRequest(I2cTypes::I2cReqestType type, QString name, QString slave_addr, QString write_data,
                       QString read_size)
    : type_{ type }, name_{ name }, slave_addr_{ slave_addr }, write_data_{ write_data }, read_size_{ read_size } {}

QDataStream& operator<<(QDataStream& out, const I2cRequest& request) {
    out << request.request_id_                //
        << static_cast<int>(request.i2c_id_)  //
        << static_cast<int>(request.type_)    //
        << request.name_                      //
        << request.slave_addr_                //
        << request.write_data_                //
        << request.read_size_                 //
        << request.status_;
    return out;
}

QDataStream& operator>>(QDataStream& in, I2cRequest& request) {
    int i2c_id;
    int type;
    in >> request.request_id_   //
        >> i2c_id               //
        >> type                 //
        >> request.name_        //
        >> request.slave_addr_  //
        >> request.write_data_  //
        >> request.read_size_   //
        >> request.status_;
    request.i2c_id_ = static_cast<I2cTypes::I2cId>(i2c_id);
    request.type_ = static_cast<I2cTypes::I2cReqestType>(type);
    return in;
}

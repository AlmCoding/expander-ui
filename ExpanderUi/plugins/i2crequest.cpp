#include "i2crequest.h"


I2cRequest::I2cRequest(I2cReqestType type, QString name, int slave_add,
                       QByteArray write_data, int read_size)
    : type_{type}, name_{name}, slave_addr_{slave_add}, write_data_{write_data},
      read_size_{read_size}
{}

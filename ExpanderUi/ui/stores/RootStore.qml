import QtQuick
import expander.I2cConfig
import expander.I2cRequestModel


Item {
    property I2cConfig i2cConfig1: I2cConfig {
        id: i2cConfig1
        slaveAddr: "0x001"
        memAddrWidth: 1 // Byte
        slaveAddrWidth: 7 // Bits
    }

    property I2cConfig i2cConfig2: I2cConfig {
        id: i2cConfig2
        slaveAddr: "0x002"
        memAddrWidth: 1 // Byte
        slaveAddrWidth: 7 // Bits
    }

    property I2cRequestModel i2cRequestModel: I2cRequestModel {
        id: i2cRequestModel
    }

}

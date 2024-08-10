#ifndef I2CCONFIG_H
#define I2CCONFIG_H

#include <QString>
#include "plugins/containers/i2c/i2cconfigstatus.h"
#include "plugins/containers/i2c/i2ctypes.h"

class I2cConfig {
   public:
    explicit I2cConfig() = default;
    explicit I2cConfig(I2cTypes::I2cId i2c_id, QString slave_addr, I2cTypes::ClockFreq clock_freq,
                       I2cTypes::MemAddrWidth mem_addr_width, I2cTypes::SlaveAddrWidth slave_addr_width);

    void setRequestId(int request_id) { request_id_ = request_id; }
    void setI2cId(I2cTypes::I2cId i2c_id) { i2c_id_ = i2c_id; }
    void setSlaveAddr(QString slave_addr) { slave_addr_ = slave_addr; }
    void setClockFreq(I2cTypes::ClockFreq clock_freq) { clock_freq_ = clock_freq; }
    void setMemAddrWidth(I2cTypes::MemAddrWidth mem_addr_width) { mem_addr_width_ = mem_addr_width; }
    void setSlaveAddrWidth(I2cTypes::SlaveAddrWidth slave_addr_width) { slave_addr_width_ = slave_addr_width; }
    void setStatus(I2cConfigStatus& status) { status_ = status; }

    int getRequestId() const { return request_id_; }
    I2cTypes::I2cId getI2cId() const { return i2c_id_; }
    QString getSlaveAddr() const { return slave_addr_; }
    I2cTypes::ClockFreq getClockFreq() const { return clock_freq_; }
    I2cTypes::MemAddrWidth getMemAddrWidth() const { return mem_addr_width_; }
    I2cTypes::SlaveAddrWidth getSlaveAddrWidth() const { return slave_addr_width_; }
    I2cConfigStatus getStatus() const { return status_; }

   private:
    int request_id_ = -1;
    I2cTypes::I2cId i2c_id_ = I2cTypes::I2cId::Undefined;
    QString slave_addr_ = "0x001";
    I2cTypes::ClockFreq clock_freq_ = I2cTypes::ClockFreq::KHz10;
    I2cTypes::MemAddrWidth mem_addr_width_ = I2cTypes::MemAddrWidth::OneByte;
    I2cTypes::SlaveAddrWidth slave_addr_width_ = I2cTypes::SlaveAddrWidth::SevenBit;

    I2cConfigStatus status_;
};

#endif  // I2CCONFIG_H

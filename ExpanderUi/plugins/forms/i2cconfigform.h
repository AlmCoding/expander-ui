#ifndef I2CCONFIGFORM_H
#define I2CCONFIGFORM_H

#include <QObject>
#include <QString>
#include "plugins/containers/i2c/i2cconfig.h"

class I2cConfigForm : public QObject {
    Q_OBJECT
    Q_PROPERTY(I2cTypes::I2cId i2cId READ getI2cId WRITE setI2cId NOTIFY i2cIdChanged)
    Q_PROPERTY(QString slaveAddr READ getSlaveAddr WRITE setSlaveAddr NOTIFY slaveAddrChanged)
    Q_PROPERTY(I2cTypes::ClockFreq clockFreq READ getClockFreq WRITE setClockFreq NOTIFY clockFreqChanged)
    Q_PROPERTY(
        I2cTypes::MemAddrWidth memAddrWidth READ getMemAddrWidth WRITE setMemAddrWidth NOTIFY memAddrWidthChanged)
    Q_PROPERTY(I2cTypes::SlaveAddrWidth slaveAddrWidth READ getSlaveAddrWidth WRITE setSlaveAddrWidth NOTIFY
                   slaveAddrWidthChanged)

   public:
    explicit I2cConfigForm(QObject* parent = nullptr);

    I2cTypes::I2cId getI2cId() const { return i2c_config_.getI2cId(); }
    QString getSlaveAddr() const { return i2c_config_.getSlaveAddr(); }
    I2cTypes::ClockFreq getClockFreq() const { return i2c_config_.getClockFreq(); }
    I2cTypes::MemAddrWidth getMemAddrWidth() const { return i2c_config_.getMemAddrWidth(); }
    I2cTypes::SlaveAddrWidth getSlaveAddrWidth() const { return i2c_config_.getSlaveAddrWidth(); }

   public slots:
    void setI2cId(I2cTypes::I2cId i2cId) {
        i2c_config_.setI2cId(i2cId);
        // emit i2cIdChanged(i2cId);
    }
    void setSlaveAddr(const QString& slaveAddr) {
        i2c_config_.setSlaveAddr(slaveAddr);
        // emit slaveAddrChanged(slaveAddr);
    }
    void setClockFreq(I2cTypes::ClockFreq clockFreq) {
        i2c_config_.setClockFreq(clockFreq);
        // emit clockFreqChanged(clockFreq);
    }
    void setMemAddrWidth(I2cTypes::MemAddrWidth memAddrWidth) {
        i2c_config_.setMemAddrWidth(memAddrWidth);
        // emit memAddrWidthChanged(memAddrWidth);
    }
    void setSlaveAddrWidth(I2cTypes::SlaveAddrWidth slaveAddrWidth) {
        i2c_config_.setSlaveAddrWidth(slaveAddrWidth);
        // emit slaveAddrWidthChanged(slaveAddrWidth);
    }
    I2cConfig getConfig() const { return i2c_config_; }

   signals:
    void i2cIdChanged(I2cTypes::I2cId id);
    void slaveAddrChanged(QString addr);
    void clockFreqChanged(I2cTypes::ClockFreq freq);
    void memAddrWidthChanged(I2cTypes::MemAddrWidth width);
    void slaveAddrWidthChanged(I2cTypes::SlaveAddrWidth width);

   private:
    I2cConfig i2c_config_;
};

#endif  // I2CCONFIGFORM_H

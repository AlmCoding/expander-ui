#ifndef I2CCONFIG_H
#define I2CCONFIG_H

#include <QObject>
#include <QString>


class I2cConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString slaveAddr READ getSlaveAddr WRITE setSlaveAddr NOTIFY slaveAddrChanged)
    Q_PROPERTY(int clockFreq READ getClockFreq WRITE setClockFreq NOTIFY clockFreqChanged)
    Q_PROPERTY(int memAddrWidth READ getMemAddrWidth WRITE setMemAddrWidth NOTIFY memAddrWidthChanged)
    Q_PROPERTY(int slaveAddrWidth READ getSlaveAddrWidth WRITE setSlaveAddrWidth NOTIFY slaveAddrWidthChanged)

public:
    explicit I2cConfig(QObject *parent = nullptr);

public slots:
    void applyConfig();

signals:
    void slaveAddrChanged();
    void clockFreqChanged();
    void memAddrWidthChanged();
    void slaveAddrWidthChanged();

private:
    QString getSlaveAddr() const { return slave_addr_; }
    void setSlaveAddr(const QString &slaveAddr) { slave_addr_ = slaveAddr; emit slaveAddrChanged(); }
    int getClockFreq() const { return clock_freq_; }
    void setClockFreq(int clockFreq) { clock_freq_ = clockFreq; emit clockFreqChanged(); }
    int getMemAddrWidth() const { return mem_addr_width_; }
    void setMemAddrWidth(int memAddrWidth) { mem_addr_width_ = memAddrWidth; emit memAddrWidthChanged(); }
    int getSlaveAddrWidth() const { return slave_addr_width_; }
    void setSlaveAddrWidth(int slaveAddrWidth)  { slave_addr_width_ = slaveAddrWidth; emit slaveAddrWidthChanged(); }

    QString slave_addr_;
    int clock_freq_ = 1000;    // 1000 kHz
    int mem_addr_width_ = 1;   // 1 Byte
    int slave_addr_width_ = 7; // 7 Bit
};

#endif // I2CCONFIG_H

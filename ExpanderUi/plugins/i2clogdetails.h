#ifndef I2CLOGDETAILS_H
#define I2CLOGDETAILS_H

#include <QObject>
#include <QString>
#include "plugins/containers/i2c/i2clog.h"
#include "plugins/containers/i2c/i2ctypes.h"

class I2cLogDetails : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString time READ getTime NOTIFY timeChanged)
    Q_PROPERTY(QString interface READ getInterface NOTIFY interfaceChanged)
    Q_PROPERTY(QString type READ getType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QString slaveAddr READ getSlaveAddr NOTIFY slaveAddrChanged)
    Q_PROPERTY(QString writeData READ getWriteData NOTIFY writeDataChanged)
    Q_PROPERTY(QString writeDataAscii READ getWriteDataAscii NOTIFY writeDataAsciiChanged)
    Q_PROPERTY(QString readData READ getReadData NOTIFY readDataChanged)
    Q_PROPERTY(QString readDataAscii READ getReadDataAscii NOTIFY readDataAsciiChanged)
    Q_PROPERTY(QString writeSize READ getWriteSize NOTIFY writeSizeChanged)
    Q_PROPERTY(QString readSize READ getReadSize NOTIFY readSizeChanged)
    Q_PROPERTY(QString status READ getStatus NOTIFY statusChanged)

   public:
    explicit I2cLogDetails(QObject* parent = nullptr);

    bool isVisible() const { return visible_; }
    QString getTime() const { return log_.getTime(); }
    QString getInterface() const { return log_.getInterfaceName(); }
    QString getType() const { return (log_.getType() == I2cTypes::I2cReqestType::MasterAction) ? "MR" : "SC"; }
    QString getName() const { return log_.getName(); }
    QString getSlaveAddr() const { return log_.getSlaveAddr(); }
    QString getWriteData() const { return log_.getWriteData(); }
    QString getWriteDataAscii() const { return log_.getWriteDataAscii(); }
    QString getReadData() const { return log_.getReadData(); }
    QString getReadDataAscii() const { return log_.getReadDataAscii(); }
    QString getWriteSize() const { return log_.getWriteSize(); }
    QString getReadSize() const { return log_.getReadSize(); }
    QString getStatus() const { return log_.getStatus(); }

   public slots:
    void setVisible(bool visible);

    void loadLog(const I2cLog& log);

   signals:
    void visibleChanged(bool visible);

    void timeChanged(QString time);
    void interfaceChanged(QString interface_name);
    void typeChanged(QString type);
    void nameChanged(QString name);
    void slaveAddrChanged(QString slave_addr);
    void writeDataChanged(QString write_data);
    void writeDataAsciiChanged(QString write_data_ascii);
    void readDataChanged(QString read_data);
    void readDataAsciiChanged(QString read_data_ascii);
    void writeSizeChanged(QString write_size);
    void readSizeChanged(QString read_size);
    void statusChanged(QString status);

   private:
    bool visible_ = false;

    I2cLog log_;
};

#endif  // I2CLOGDETAILS_H

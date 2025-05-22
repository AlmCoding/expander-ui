#ifndef I2CREQUESTFORM_H
#define I2CREQUESTFORM_H

#include <QObject>
#include <QString>
#include "plugins/containers/i2c/i2crequest.h"
#include "plugins/containers/i2c/i2ctypes.h"

class I2cRequestForm : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool externalUpdate READ getExternalUpdate WRITE setExternalUpdate NOTIFY externalUpdateChanged)
    Q_PROPERTY(bool hexUpdate READ getHexUpdate WRITE setHexUpdate NOTIFY hexUpdateChanged)
    Q_PROPERTY(bool asciiUpdate READ getAsciiUpdate WRITE setAsciiUpdate NOTIFY asciiUpdateChanged)
    Q_PROPERTY(I2cTypes::I2cReqestType type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString slaveAddress READ getSlaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)
    Q_PROPERTY(QString writeData READ getWriteData WRITE setWriteData NOTIFY writeDataChanged)
    Q_PROPERTY(QString writeDataAscii READ getWriteDataAscii WRITE setWriteDataAscii NOTIFY writeDataAsciiChanged)
    Q_PROPERTY(QString writeSize READ getWriteSize WRITE setWriteSize NOTIFY writeSizeChanged)
    Q_PROPERTY(QString readSize READ getReadSize WRITE setReadSize NOTIFY readSizeChanged)

   public:
    explicit I2cRequestForm(QObject* parent = nullptr);

    bool isVisible() const { return visible_; }
    bool getExternalUpdate() const { return external_update_; }
    bool getHexUpdate() const { return hex_update_; }
    bool getAsciiUpdate() const { return ascii_update_; }
    I2cTypes::I2cReqestType getType() const { return type_; }
    QString getName() const { return name_; }
    QString getSlaveAddress() const { return slave_addr_; }
    QString getWriteData() const { return write_data_; }
    QString getWriteDataAscii() const { return write_data_ascii_; }
    QString getWriteSize() const { return write_size_; }
    QString getReadSize() const { return read_size_; }

   public slots:
    void setVisible(bool visible);
    void setExternalUpdate(bool externalUpdate);
    void setHexUpdate(bool hexUpdate);
    void setAsciiUpdate(bool asciiUpdate);

    void setType(I2cTypes::I2cReqestType type);
    void setName(const QString& name);
    void setSlaveAddress(const QString& slave_addr);
    void setWriteData(const QString& write_data);
    void setWriteDataAscii(const QString& write_data_ascii);
    void setWriteSize(const QString& write_size);
    void setReadSize(const QString& read_size);

    void loadRequest(const I2cRequest& request);
    void clearRequest();

   signals:
    void visibleChanged(bool visible);
    void externalUpdateChanged(bool external_update);
    void hexUpdateChanged(bool hex_update);
    void asciiUpdateChanged(bool ascii_update);
    void typeChanged(I2cTypes::I2cReqestType type);
    void nameChanged(QString name);
    void slaveAddressChanged(QString addr);
    void writeDataChanged(QString data);
    void writeDataAsciiChanged(QString data);
    void writeSizeChanged(QString size);
    void readSizeChanged(QString size);
    void requestChanged(I2cRequest request);

   private:
    bool visible_ = false;
    bool external_update_ = true;  // Init with true to avoid binding loop
    bool hex_update_ = false;
    bool ascii_update_ = false;

    I2cTypes::I2cReqestType type_;
    QString name_;
    QString slave_addr_;
    QString write_data_;
    QString write_data_ascii_;
    QString write_size_;
    QString read_size_;

    I2cRequest request_;
};

#endif  // I2CREQUESTFORM_H

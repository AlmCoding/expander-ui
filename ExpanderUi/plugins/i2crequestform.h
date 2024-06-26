#ifndef I2CREQUESTFORM_H
#define I2CREQUESTFORM_H

#include <QObject>
#include <QString>
#include "plugins/i2crequest.h"

class I2cRequestForm : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool externalUpdate READ getExternalUpdate WRITE setExternalUpdate NOTIFY externalUpdateChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString slaveAddress READ getSlaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)
    Q_PROPERTY(QString writeData READ getWriteData WRITE setWriteData NOTIFY writeDataChanged)
    Q_PROPERTY(QString writeSize READ getWriteSize WRITE setWriteSize NOTIFY writeSizeChanged)
    Q_PROPERTY(QString readSize READ getReadSize WRITE setReadSize NOTIFY readSizeChanged)

   public:
    explicit I2cRequestForm(QObject* parent = nullptr);

    bool isVisible() const { return visible_; }
    bool getExternalUpdate() const { return external_update_; }
    QString getName() const { return name_; }
    QString getSlaveAddress() const { return slave_addr_; }
    QString getWriteData() const { return write_data_; }
    QString getWriteSize() const { return write_size_; }
    QString getReadSize() const { return read_size_; }

   public slots:
    void setVisible(bool visible) {
        visible_ = visible;
        emit visibleChanged(visible_);
    }
    void setExternalUpdate(bool externalUpdate) {
        external_update_ = externalUpdate;
        emit externalUpdateChanged(external_update_);
    }
    void setName(const QString& name) {
        name_ = name;
        emit nameChanged(name_);

        request_.setName(name_);
        if (external_update_ == false)
            emit requestChanged(request_);
        
    }
    void setSlaveAddress(const QString& slave_addr) {
        slave_addr_ = slave_addr;
        emit slaveAddressChanged(slave_addr_);

        request_.setSlaveAddr(slave_addr_);
        if (external_update_ == false)
            emit requestChanged(request_);
    }
    void setWriteData(const QString& write_data) {
        write_data_ = write_data;
        emit writeDataChanged(write_data_);

        request_.setWriteData(write_data_);
        setWriteSize(request_.getWriteSize());
        if (external_update_ == false)
            emit requestChanged(request_);
    }
    void setWriteSize(const QString& write_size) {
        write_size_ = write_size;
        emit writeSizeChanged(write_size_);
    }
    void setReadSize(const QString& read_size) {
        read_size_ = read_size;
        emit readSizeChanged(read_size_);

        request_.setReadSize(read_size_);
        if (external_update_ == false)
            emit requestChanged(request_);
    }

    void loadRequest(const I2cRequest& request);
    void clearRequest();

   signals:
    void visibleChanged(bool visible);
    void externalUpdateChanged(bool externalUpdate);
    void nameChanged(QString name);
    void slaveAddressChanged(QString addr);
    void writeDataChanged(QString data);
    void writeSizeChanged(QString size);
    void readSizeChanged(QString size);

    void requestChanged(I2cRequest request);

   private:
    bool visible_ = false;
    bool external_update_ = false;

    QString name_;
    QString slave_addr_;
    QString write_data_;
    QString write_size_;
    QString read_size_;

    I2cRequest request_;
};

#endif  // I2CREQUESTFORM_H

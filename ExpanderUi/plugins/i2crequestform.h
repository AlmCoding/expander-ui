#ifndef I2CREQUESTFORM_H
#define I2CREQUESTFORM_H

#include <QObject>
#include <QString>
#include "plugins/i2crequest.h"

class I2cRequestForm : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString slaveAddress READ getSlaveAddress WRITE setSlaveAddress NOTIFY slaveAddressChanged)
    Q_PROPERTY(QString writeData READ getWriteData WRITE setWriteData NOTIFY writeDataChanged)
    Q_PROPERTY(int writeSize READ getWriteSize WRITE setWriteSize NOTIFY writeSizeChanged)
    Q_PROPERTY(int readSize READ getReadSize WRITE setReadSize NOTIFY readSizeChanged)

   public:
    explicit I2cRequestForm(QObject* parent = nullptr);

    bool isVisible() const { return is_visible_; }
    QString getName() const { return name_; }
    QString getSlaveAddress() const { return slave_address_; }
    QString getWriteData() const { return write_data_; }
    int getWriteSize() const { return write_size_; }
    int getReadSize() const { return read_size_; }

   public slots:
    void setVisible(bool visible) {
        is_visible_ = visible;
        emit visibleChanged();
    }
    void setName(const QString& name) {
        name_ = name;
        request_.setName(name);
        emit nameChanged();
        emit requestChanged(request_);
    }
    void setSlaveAddress(const QString& slave_address) {
        slave_address_ = slave_address;
        emit slaveAddressChanged();
    }
    void setWriteData(const QString& write_data) {
        write_data_ = write_data;
        emit writeDataChanged();
    }
    void setWriteSize(int write_size) {
        write_size_ = write_size;
        emit writeSizeChanged();
    }
    void setReadSize(int read_size) {
        read_size_ = read_size;
        emit readSizeChanged();
    }

    void loadRequest(I2cRequest request);
    void clearRequest();

   signals:
    void visibleChanged();
    void nameChanged();
    void slaveAddressChanged();
    void writeDataChanged();
    void writeSizeChanged();
    void readSizeChanged();

    void requestChanged(I2cRequest request);

   private:
    bool is_visible_ = false;
    QString name_;
    QString slave_address_;
    QString write_data_;
    int write_size_ = 0;
    int read_size_ = 0;

    I2cRequest request_;
};

#endif  // I2CREQUESTFORM_H

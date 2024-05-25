#include "i2crequestform.h"

I2cRequestForm::I2cRequestForm(QObject* parent) : QObject{ parent } {}

void I2cRequestForm::loadRequest(I2cRequest request) {
    request_ = request;

    setName(request.getName());
    setSlaveAddress(QString::number(request.getSlaveAddr()));
    setWriteData(request.getWriteData());
    setWriteSize(request.getWriteData().size());
    setReadSize(request.getReadSize());
}

void I2cRequestForm::clearRequest()
{
    I2cRequest request{};
    request.setName(request_.getName());
    loadRequest(request);
    emit requestChanged(request_);
}


#include "i2crequestform.h"

I2cRequestForm::I2cRequestForm(QObject* parent) : QObject{ parent } {}

void I2cRequestForm::loadRequest(const I2cRequest& request) {
    request_ = request;

    setName(request.getName());
    setSlaveAddress(request.getSlaveAddr());
    setWriteData(request.getWriteData());
    setWriteSize(request.getWriteSize());
    setReadSize(request.getReadSize());
}

void I2cRequestForm::clearRequest()
{
    I2cRequest request{};
    // request.setName(request_.getName());
    loadRequest(request);
    emit requestChanged(request_);
}

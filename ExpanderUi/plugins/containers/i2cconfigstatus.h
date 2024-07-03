#ifndef I2CCONFIGSTATUS_H
#define I2CCONFIGSTATUS_H

class I2cConfigStatus {
   public:
    enum class RequestStatus {
        Ok = 0,
        InvalidClockFreq,
        InvalidSlaveAddr,
        InvalidSlaveAddrWidth,
        InvalidMemAddrWidth,
        InterfaceError,
    };

    I2cConfigStatus(int request_id, RequestStatus status);

    int getRequestId() const { return request_id_; }
    RequestStatus getStatus() const { return status_; }

   private:
    int request_id_ = -1;
    RequestStatus status_;
};

#endif  // I2CCONFIGSTATUS_H

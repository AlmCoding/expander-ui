#ifndef I2CCONFIGSTATUS_H
#define I2CCONFIGSTATUS_H

class I2cConfigStatus {
   public:
    enum class StatusCode {
        Ok = 0,
        InvalidClockFreq,
        InvalidSlaveAddr,
        InvalidSlaveAddrWidth,
        InvalidMemAddrWidth,
        InterfaceError,
    };

    I2cConfigStatus(int request_id, StatusCode status_code);

    int getRequestId() const { return request_id_; }
    StatusCode getStatusCode() const { return status_code_; }

   private:
    int request_id_ = -1;
    StatusCode status_code_;
};

#endif  // I2CCONFIGSTATUS_H

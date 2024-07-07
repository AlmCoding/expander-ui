#ifndef I2CREQUESTSTATUS_H
#define I2CREQUESTSTATUS_H

#include <QString>

class I2cRequestStatus {
   public:
    enum class StatusCode {
        NotInit = 0,
        NoSpace,
        Pending,
        Ongoing,
        Complete,
        SlaveBusy,
        InterfaceError,
    };

    I2cRequestStatus() = default;
    I2cRequestStatus(int request_id, StatusCode status_code, const QString& read_data);

    void setRequestId(int request_id) { request_id_ = request_id; }
    void setStatusCode(StatusCode status_code) { status_code_ = status_code; }
    void setReadData(const QString& read_data) { read_data_ = read_data; }

    int getRequestId() const { return request_id_; }
    StatusCode getStatusCode() const { return status_code_; }
    QString getReadData() const { return read_data_; }
    QString getReadSize() const;

   private:
    int request_id_ = -1;
    StatusCode status_code_ = StatusCode::InterfaceError;
    QString read_data_;
};

#endif  // I2CREQUESTSTATUS_H

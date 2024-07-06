#include "i2crequeststatus.h"

I2cRequestStatus::I2cRequestStatus(int request_id, StatusCode status_code, const QString& read_data)
    : request_id_{ request_id }, status_code_{ status_code }, read_data_{ read_data } {}

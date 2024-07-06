#include "i2cconfigstatus.h"

I2cConfigStatus::I2cConfigStatus(int request_id, StatusCode status_code)
    : request_id_{ request_id }, status_code_{ status_code } {}

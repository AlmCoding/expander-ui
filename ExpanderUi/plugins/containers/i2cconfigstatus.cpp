#include "i2cconfigstatus.h"

I2cConfigStatus::I2cConfigStatus(int request_id, RequestStatus status) : request_id_{ request_id }, status_{ status } {}

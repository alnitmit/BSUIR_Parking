#include "ParkingLotNotFoundError.h"

ParkingLotNotFoundError::ParkingLotNotFoundError(const std::string& message)
    : ParkingSystemError(message) {}

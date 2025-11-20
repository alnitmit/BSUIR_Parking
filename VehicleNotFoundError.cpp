#include "VehicleNotFoundError.h"

VehicleNotFoundError::VehicleNotFoundError(const std::string& message) 
    : ParkingSystemError(message) {}


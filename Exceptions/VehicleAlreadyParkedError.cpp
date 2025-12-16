#include "VehicleAlreadyParkedError.h"

VehicleAlreadyParkedError::VehicleAlreadyParkedError(const std::string& message) 
    : ParkingSystemError(message) {}


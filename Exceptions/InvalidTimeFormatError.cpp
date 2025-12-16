#include "InvalidTimeFormatError.h"

InvalidTimeFormatError::InvalidTimeFormatError(const std::string& message) 
    : ParkingSystemError(message) {}


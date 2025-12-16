#include "InvalidLicensePlateError.h"

InvalidLicensePlateError::InvalidLicensePlateError(const std::string& message) 
    : ParkingSystemError(message) {}


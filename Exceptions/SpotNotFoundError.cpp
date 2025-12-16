#include "SpotNotFoundError.h"

SpotNotFoundError::SpotNotFoundError(const std::string& message) 
    : ParkingSystemError(message) {}


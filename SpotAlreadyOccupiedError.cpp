#include "SpotAlreadyOccupiedError.h"

SpotAlreadyOccupiedError::SpotAlreadyOccupiedError(const std::string& message) 
    : ParkingSystemError(message) {}


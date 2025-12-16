#include "SpotAlreadyFreeError.h"

SpotAlreadyFreeError::SpotAlreadyFreeError(const std::string& message) 
    : ParkingSystemError(message) {}


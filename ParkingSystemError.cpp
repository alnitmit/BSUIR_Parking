#include "ParkingSystemError.h"

ParkingSystemError::ParkingSystemError(const std::string& message) : message_(message) {}

const char* ParkingSystemError::what() const noexcept {
    return message_.c_str();
}

std::string ParkingSystemError::getMessage() const {
    return message_;
}


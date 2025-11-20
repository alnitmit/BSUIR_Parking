#ifndef INVALIDLICENSEPLATEERROR_H
#define INVALIDLICENSEPLATEERROR_H

#include "ParkingSystemError.h"

class InvalidLicensePlateError : public ParkingSystemError {
public:
    explicit InvalidLicensePlateError(const std::string& message = "Неверный формат номерного знака.");
};

#endif

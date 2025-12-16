#ifndef DUPLICATEVEHICLEERROR_H
#define DUPLICATEVEHICLEERROR_H

#include "ParkingSystemError.h"

class DuplicateVehicleError : public ParkingSystemError {
public:
    explicit DuplicateVehicleError(const std::string& message = "Транспортное средство уже существует.");
};

#endif

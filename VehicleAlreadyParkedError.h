#ifndef VEHICLEALREADYPARKEDERROR_H
#define VEHICLEALREADYPARKEDERROR_H

#include "ParkingSystemError.h"

class VehicleAlreadyParkedError : public ParkingSystemError {
public:
    explicit VehicleAlreadyParkedError(const std::string& message = "Транспортное средство уже припарковано.");
};

#endif

#ifndef VEHICLENOTFOUNDERROR_H
#define VEHICLENOTFOUNDERROR_H

#include "ParkingSystemError.h"

class VehicleNotFoundError : public ParkingSystemError {
public:
    explicit VehicleNotFoundError(const std::string& message = "Транспортное средство не найдено.");
};

#endif

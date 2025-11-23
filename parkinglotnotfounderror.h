#ifndef PARKINGLOTNOTFOUNDERROR_H
#define PARKINGLOTNOTFOUNDERROR_H

#include "ParkingSystemError.h"

class ParkingLotNotFoundError : public ParkingSystemError {
public:
    explicit ParkingLotNotFoundError(const std::string& message = "Парковка не найдена.");
};

#endif

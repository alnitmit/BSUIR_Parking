#ifndef SPOTALREADYOCCUPIEDERROR_H
#define SPOTALREADYOCCUPIEDERROR_H

#include "ParkingSystemError.h"

class SpotAlreadyOccupiedError : public ParkingSystemError {
public:
    explicit SpotAlreadyOccupiedError(const std::string& message = "Парковочное место уже занято.");
};

#endif

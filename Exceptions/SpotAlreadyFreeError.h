#ifndef SPOTALREADYFREEERROR_H
#define SPOTALREADYFREEERROR_H

#include "ParkingSystemError.h"

class SpotAlreadyFreeError : public ParkingSystemError {
public:
    explicit SpotAlreadyFreeError(const std::string& message = "Парковочное место уже свободно.");
};

#endif

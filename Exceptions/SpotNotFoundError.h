#ifndef SPOTNOTFOUNDERROR_H
#define SPOTNOTFOUNDERROR_H

#include "ParkingSystemError.h"

class SpotNotFoundError : public ParkingSystemError {
public:
    explicit SpotNotFoundError(const std::string& message = "Парковочное место не найдено.");
};

#endif

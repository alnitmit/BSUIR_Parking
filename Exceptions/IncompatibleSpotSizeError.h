#ifndef INCOMPATIBLESPOTSIZEERROR_H
#define INCOMPATIBLESPOTSIZEERROR_H

#include "ParkingSystemError.h"

class IncompatibleSpotSizeError : public ParkingSystemError {
public:
    explicit IncompatibleSpotSizeError(const std::string& message = "Несовместимый размер парковочного места.");
};

#endif

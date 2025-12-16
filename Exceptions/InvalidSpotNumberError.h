#ifndef INVALIDSPOTNUMBERERROR_H
#define INVALIDSPOTNUMBERERROR_H

#include "ParkingSystemError.h"

class InvalidSpotNumberError : public ParkingSystemError {
public:
    explicit InvalidSpotNumberError(const std::string& message = "Неверный номер парковочного места.");
};

#endif

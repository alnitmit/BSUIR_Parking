#ifndef INVALIDTIMEFORMATERROR_H
#define INVALIDTIMEFORMATERROR_H

#include "ParkingSystemError.h"

class InvalidTimeFormatError : public ParkingSystemError {
public:
    explicit InvalidTimeFormatError(const std::string& message = "Неверный формат времени.");
};

#endif

#ifndef INPUTCANCELLEDERROR_H
#define INPUTCANCELLEDERROR_H

#include "ParkingSystemError.h"

class InputCancelledError : public ParkingSystemError {
public:
    explicit InputCancelledError(const std::string& message = "Ввод отменен пользователем.");
};

#endif

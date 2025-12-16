#ifndef EXPORTERROR_H
#define EXPORTERROR_H

#include "ParkingSystemError.h"

class ExportError : public ParkingSystemError {
public:
    explicit ExportError(const std::string& message = "Ошибка экспорта данных.");
};

#endif

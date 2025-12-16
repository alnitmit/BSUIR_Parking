#ifndef FILEIOEXCEPTION_H
#define FILEIOEXCEPTION_H

#include "ParkingSystemError.h"

class FileIOException : public ParkingSystemError {
public:
    explicit FileIOException(const std::string& message = "Ошибка ввода-вывода файла.");
};

#endif

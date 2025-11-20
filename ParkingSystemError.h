#ifndef PARKINGSYSTEMERROR_H
#define PARKINGSYSTEMERROR_H

#include <string>
#include <exception>

class ParkingSystemError : public std::exception {
public:
    explicit ParkingSystemError(const std::string& message = "");
    
    const char* what() const noexcept override;
    std::string getMessage() const;

private:
    std::string message_;
};

#endif

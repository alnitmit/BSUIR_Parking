#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <string>
#include <string_view>

class VehicleData {
public:
    VehicleData();
    VehicleData(std::string_view type, std::string_view model, std::string_view licensePlate);  // Исправлено: string_view

    std::string getType() const;
    void setType(std::string_view type);  // Исправлено: string_view

    std::string getModel() const;
    void setModel(std::string_view model);  // Исправлено: string_view

    std::string getLicensePlate() const;
    void setLicensePlate(std::string_view licensePlate);  // Исправлено: string_view

    bool isParked() const;
    void setParked(bool parked);

    std::string getCargoType() const;
    void setCargoType(std::string_view cargoType);  // Исправлено: string_view

private:
    std::string type_;
    std::string model_;
    std::string licensePlate_;
    bool isParked_ = false;  // Исправлено: инициализация в классе
    std::string cargoType_;
};

#endif

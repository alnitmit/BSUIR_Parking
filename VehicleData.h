#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <string>
#include <string_view>

class VehicleData {
public:
    VehicleData() = default;  // Исправлено: = default
    VehicleData(std::string_view type, std::string_view model, std::string_view licensePlate);

    std::string getType() const;
    void setType(std::string_view type);

    std::string getModel() const;
    void setModel(std::string_view model);

    std::string getLicensePlate() const;
    void setLicensePlate(std::string_view licensePlate);

    bool isParked() const;
    void setParked(bool parked);

    std::string getCargoType() const;
    void setCargoType(std::string_view cargoType);

private:
    std::string type_;
    std::string model_;
    std::string licensePlate_;
    bool isParked_ = false;
    std::string cargoType_;
};

#endif

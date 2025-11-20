#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <string>

class VehicleData {
public:
    VehicleData();
    VehicleData(const std::string& type, const std::string& model, const std::string& licensePlate);
    
    std::string getType() const;
    void setType(const std::string& type);
    
    std::string getModel() const;
    void setModel(const std::string& model);
    
    std::string getLicensePlate() const;
    void setLicensePlate(const std::string& licensePlate);
    
    bool isParked() const;
    void setParked(bool parked);
    
    std::string getCargoType() const;
    void setCargoType(const std::string& cargoType);

private:
    std::string type_;
    std::string model_;
    std::string licensePlate_;
    bool isParked_;
    std::string cargoType_;
};

#endif

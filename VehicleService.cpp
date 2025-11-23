#include "VehicleService.h"
#include <algorithm>
#include <memory>

bool VehicleService::addVehicle(const VehicleData& vehicle, std::vector<VehicleData>& vehicles) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
                           [&vehicle](const VehicleData& v) {
                               return v.getLicensePlate() == vehicle.getLicensePlate();
                           });

    if (it != vehicles.end()) {
        return false;
    }

    vehicles.push_back(vehicle);
    return true;
}

bool VehicleService::removeVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto it = std::remove_if(vehicles.begin(), vehicles.end(),
                             [&licensePlate](const VehicleData& vehicle) {
                                 return vehicle.getLicensePlate() == licensePlate;
                             });

    if (it != vehicles.end()) {
        vehicles.erase(it, vehicles.end());
        return true;
    }
    return false;
}

VehicleData* VehicleService::findVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
                           [&licensePlate](const VehicleData& vehicle) {
                               return vehicle.getLicensePlate() == licensePlate;
                           });

    if (it != vehicles.end()) {
        return &(*it); // Замена std::to_address
    }
    return nullptr;
}

const VehicleData* VehicleService::findVehicle(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
                           [&licensePlate](const VehicleData& vehicle) {
                               return vehicle.getLicensePlate() == licensePlate;
                           });

    if (it != vehicles.end()) {
        return &(*it); // Замена std::to_address
    }
    return nullptr;
}

bool VehicleService::isVehicleParked(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    const VehicleData* vehicle = findVehicle(licensePlate, vehicles);
    return vehicle ? vehicle->isParked() : false;
}

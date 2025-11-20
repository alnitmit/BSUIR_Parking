#include "VehicleService.h"
#include "DuplicateVehicleError.h"
#include "VehicleNotFoundError.h"
#include <algorithm>

bool VehicleService::addVehicle(VehicleData vehicle, std::vector<VehicleData>& vehicles) {
    if (findVehicle(vehicle.getLicensePlate(), vehicles)) {
        throw DuplicateVehicleError("Vehicle with license plate " + vehicle.getLicensePlate() + " already exists");
    }
    vehicles.push_back(vehicle);
    return true;
}

bool VehicleService::removeVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto it = std::remove_if(vehicles.begin(), vehicles.end(),
        [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    
    if (it != vehicles.end()) {
        vehicles.erase(it, vehicles.end());
        return true;
    }
    return false;
}

VehicleData* VehicleService::findVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&licensePlate](VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    return (it != vehicles.end()) ? &(*it) : nullptr;
}

const VehicleData* VehicleService::findVehicle(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
        [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    return (it != vehicles.end()) ? &(*it) : nullptr;
}

bool VehicleService::isVehicleParked(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    const VehicleData* vehicle = findVehicle(licensePlate, vehicles);
    return vehicle ? vehicle->isParked() : false;
}

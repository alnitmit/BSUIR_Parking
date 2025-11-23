#include "VehicleService.h"
#include <algorithm>
#include <memory>
#include <ranges>

bool VehicleService::addVehicle(const VehicleData& vehicle, std::vector<VehicleData>& vehicles) {
    if (auto it = std::ranges::find_if(vehicles, [&vehicle](const VehicleData& v) {
            return v.getLicensePlate() == vehicle.getLicensePlate();
        }); it != vehicles.end()) {
        return false;
    }

    vehicles.push_back(vehicle);
    return true;
}

bool VehicleService::removeVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto [first, last] = std::ranges::remove_if(vehicles, [&licensePlate](const VehicleData& vehicle) {
        return vehicle.getLicensePlate() == licensePlate;
    });

    if (first != last) {
        vehicles.erase(first, last);
        return true;
    }
    return false;
}

VehicleData* VehicleService::findVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    if (auto it = std::ranges::find_if(vehicles, [&licensePlate](const VehicleData& vehicle) {
            return vehicle.getLicensePlate() == licensePlate;
        }); it != vehicles.end()) {
        return std::to_address(it);
    }
    return nullptr;
}

const VehicleData* VehicleService::findVehicle(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    if (auto it = std::ranges::find_if(vehicles, [&licensePlate](const VehicleData& vehicle) {
            return vehicle.getLicensePlate() == licensePlate;
        }); it != vehicles.end()) {
        return std::to_address(it);
    }
    return nullptr;
}

bool VehicleService::isVehicleParked(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    const VehicleData* vehicle = findVehicle(licensePlate, vehicles);
    return vehicle ? vehicle->isParked() : false;
}

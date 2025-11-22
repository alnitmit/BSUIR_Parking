#include "VehicleService.h"
#include "DuplicateVehicleError.h"
#include "VehicleNotFoundError.h"
#include <algorithm>
#include <ranges>
#include <memory>

bool VehicleService::addVehicle(const VehicleData& vehicle, std::vector<VehicleData>& vehicles) {  // Исправлено: const ссылка
    if (findVehicle(vehicle.getLicensePlate(), vehicles)) {
        throw DuplicateVehicleError("Vehicle with license plate " + vehicle.getLicensePlate() + " already exists");
    }
    vehicles.push_back(vehicle);
    return true;
}

bool VehicleService::removeVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto it = std::ranges::remove_if(vehicles,  // Исправлено: ranges::remove_if
                                     [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });

    if (it != vehicles.end()) {
        vehicles.erase(it.begin(), vehicles.end());
        return true;
    }
    return false;
}

VehicleData* VehicleService::findVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles) {
    auto it = std::ranges::find_if(vehicles,  // Исправлено: ranges::find_if
                                   [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    return (it != vehicles.end()) ? std::to_address(it) : nullptr;  // Исправлено: to_address
}

const VehicleData* VehicleService::findVehicle(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    auto it = std::ranges::find_if(vehicles,  // Исправлено: ranges::find_if
                                   [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    return (it != vehicles.end()) ? std::to_address(it) : nullptr;  // Исправлено: to_address
}

bool VehicleService::isVehicleParked(const std::string& licensePlate, const std::vector<VehicleData>& vehicles) {
    const VehicleData* vehicle = findVehicle(licensePlate, vehicles);
    return vehicle ? vehicle->isParked() : false;
}

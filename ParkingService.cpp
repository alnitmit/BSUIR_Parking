#include "ParkingService.h"
#include "VehicleNotFoundError.h"
#include "SpotNotFoundError.h"
#include "SpotAlreadyOccupiedError.h"
#include "VehicleAlreadyParkedError.h"
#include "SpotAlreadyFreeError.h"
#include "IncompatibleSpotSizeError.h"
#include <algorithm>

bool ParkingService::parkVehicle(const std::string& licensePlate, 
                                 int lotId, 
                                 int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 const std::vector<VehicleData>& vehicles) {
    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(),
        [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    
    if (vehicleIt == vehicles.end()) {
        throw VehicleNotFoundError("Vehicle with license plate " + licensePlate + " not found");
    }
    
    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        throw SpotNotFoundError("Parking lot with ID " + std::to_string(lotId) + " not found");
    }
    
    ParkingSpotData* spot = findSpot(lotIt->second, spotNumber);
    if (!spot) {
        throw SpotNotFoundError("Parking spot " + std::to_string(spotNumber) + " not found");
    }
    
    if (spot->isOccupied()) {
        throw SpotAlreadyOccupiedError();
    }
    
    if (vehicleIt->isParked()) {
        throw VehicleAlreadyParkedError();
    }
    
    if (!isSpotCompatible(*vehicleIt, *spot)) {
        throw IncompatibleSpotSizeError();
    }
    
    spot->setOccupied(true);
    spot->setVehicleLicensePlate(licensePlate);
    
    return true;
}

bool ParkingService::releaseSpot(int lotId, 
                                  int spotNumber,
                                  std::map<int, ParkingLotData>& lots,
                                  std::vector<VehicleData>& vehicles) {
    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        throw SpotNotFoundError("Parking lot with ID " + std::to_string(lotId) + " not found");
    }
    
    ParkingSpotData* spot = findSpot(lotIt->second, spotNumber);
    if (!spot) {
        throw SpotNotFoundError("Parking spot " + std::to_string(spotNumber) + " not found");
    }
    
    if (!spot->isOccupied()) {
        throw SpotAlreadyFreeError();
    }
    
    std::string licensePlate = spot->getVehicleLicensePlate();
    spot->setOccupied(false);
    spot->setVehicleLicensePlate("");
    spot->clearParkingTime();
    
    auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(),
        [&licensePlate](VehicleData& v) { return v.getLicensePlate() == licensePlate; });
    
    if (vehicleIt != vehicles.end()) {
        vehicleIt->setParked(false);
    }
    
    return true;
}

bool ParkingService::isSpotCompatible(const VehicleData& vehicle, const ParkingSpotData& spot) {
    if (vehicle.getType() == "Truck" && spot.getSize() == ParkingSpotData::Size::COMPACT) {
        return false;
    }
    return true;
}

ParkingSpotData* ParkingService::findSpot(ParkingLotData& lot, int spotNumber) {
    for (auto& spot : lot.getSpots()) {
        if (spot.getNumber() == spotNumber) {
            return &spot;
        }
    }
    return nullptr;
}

const ParkingSpotData* ParkingService::findSpot(const ParkingLotData& lot, int spotNumber) {
    for (const auto& spot : lot.getSpots()) {
        if (spot.getNumber() == spotNumber) {
            return &spot;
        }
    }
    return nullptr;
}

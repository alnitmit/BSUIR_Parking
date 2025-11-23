#include "ParkingService.h"
#include "VehicleService.h"
#include "SpotNotFoundError.h"
#include "SpotAlreadyOccupiedError.h"
#include "VehicleNotFoundError.h"
#include "VehicleAlreadyParkedError.h"
#include "SpotAlreadyFreeError.h"
#include "IncompatibleSpotSizeError.h"
#include <format>

bool ParkingService::parkVehicle(const std::string& licensePlate, int lotId, int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 std::vector<VehicleData>& vehicles) {
    VehicleData* vehicle = VehicleService::findVehicle(licensePlate, vehicles);
    if (!vehicle) {
        throw VehicleNotFoundError(std::format("Vehicle not found: {}", licensePlate));
    }

    if (vehicle->isParked()) {
        throw VehicleAlreadyParkedError(std::format("Vehicle already parked: {}", licensePlate));
    }

    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        throw SpotNotFoundError(std::format("Parking lot with ID {} not found", lotId));
    }

    ParkingSpotData* spot = lotIt->second.getSpot(spotNumber);
    if (!spot) {
        throw SpotNotFoundError(std::format("Parking spot {} not found", spotNumber));
    }

    if (spot->isOccupied()) {
        throw SpotAlreadyOccupiedError(std::format("Spot already occupied: {}", spotNumber));
    }

    if (!isVehicleSizeCompatible(*vehicle, *spot)) {
        throw IncompatibleSpotSizeError("Vehicle size incompatible with spot");
    }

    spot->setOccupied(true);
    spot->setVehicleLicensePlate(licensePlate);
    vehicle->setParked(true);

    return true;
}

bool ParkingService::releaseSpot(int lotId, int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 std::vector<VehicleData>& vehicles) {
    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        throw SpotNotFoundError(std::format("Parking lot with ID {} not found", lotId));
    }

    ParkingSpotData* spot = lotIt->second.getSpot(spotNumber);
    if (!spot) {
        throw SpotNotFoundError(std::format("Parking spot {} not found", spotNumber));
    }

    if (!spot->isOccupied()) {
        throw SpotAlreadyFreeError(std::format("Spot already free: {}", spotNumber));
    }

    std::string licensePlate = spot->getVehicleLicensePlate();
    spot->setOccupied(false);
    spot->setVehicleLicensePlate("");

    if (VehicleData* vehicle = VehicleService::findVehicle(licensePlate, vehicles); vehicle) {
        vehicle->setParked(false);
    }

    return true;
}

ParkingSpotData* ParkingService::findSpot(ParkingLotData& lot, int spotNumber) {
    return lot.getSpot(spotNumber);
}

const ParkingSpotData* ParkingService::findSpot(const ParkingLotData& lot, int spotNumber) {
    return lot.getSpot(spotNumber);
}

bool ParkingService::isVehicleSizeCompatible(const VehicleData& vehicle, const ParkingSpotData& spot) {
    if (vehicle.getType() == "Truck" && spot.getSize() == ParkingSpotData::Size::Compact) {
        return false;
    }
    return true;
}

bool ParkingService::isSpotCompatible(const VehicleData& vehicle, const ParkingSpotData& spot) {
    return isVehicleSizeCompatible(vehicle, spot);
}

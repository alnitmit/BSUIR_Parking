#include "ParkingService.h"
#include "VehicleService.h"
#include "SpotNotFoundError.h"
#include "SpotAlreadyOccupiedError.h"
#include "VehicleNotFoundError.h"
#include "VehicleAlreadyParkedError.h"
#include "SpotAlreadyFreeError.h"
#include "IncompatibleSpotSizeError.h"
#include <sstream>

bool ParkingService::parkVehicle(const std::string& licensePlate, int lotId, int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 const std::vector<VehicleData>& vehicles) {
    const VehicleData* vehicle = VehicleService::findVehicle(licensePlate, vehicles);
    if (!vehicle) {
        throw VehicleNotFoundError("Vehicle not found: " + licensePlate);
    }

    if (vehicle->isParked()) {
        throw VehicleAlreadyParkedError("Vehicle already parked: " + licensePlate);
    }

    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        std::stringstream ss;
        ss << "Parking lot with ID " << lotId << " not found";
        throw SpotNotFoundError(ss.str());
    }

    ParkingSpotData* spot = lotIt->second.getSpot(spotNumber);
    if (!spot) {
        std::stringstream ss;
        ss << "Parking spot " << spotNumber << " not found";
        throw SpotNotFoundError(ss.str());
    }

    if (spot->isOccupied()) {
        throw SpotAlreadyOccupiedError("Spot already occupied: " + std::to_string(spotNumber));
    }

    if (!isVehicleSizeCompatible(*vehicle, *spot)) {
        throw IncompatibleSpotSizeError("Vehicle size incompatible with spot");
    }

    spot->setOccupied(true);
    spot->setVehicleLicensePlate(licensePlate);
    const_cast<VehicleData*>(vehicle)->setParked(true);

    return true;
}

bool ParkingService::releaseSpot(int lotId, int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 std::vector<VehicleData>& vehicles) {
    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        std::stringstream ss;
        ss << "Parking lot with ID " << lotId << " not found";
        throw SpotNotFoundError(ss.str());
    }

    ParkingSpotData* spot = lotIt->second.getSpot(spotNumber);
    if (!spot) {
        std::stringstream ss;
        ss << "Parking spot " << spotNumber << " not found";
        throw SpotNotFoundError(ss.str());
    }

    if (!spot->isOccupied()) {
        throw SpotAlreadyFreeError("Spot already free: " + std::to_string(spotNumber));
    }

    std::string licensePlate = spot->getVehicleLicensePlate();
    spot->setOccupied(false);
    spot->setVehicleLicensePlate("");

    VehicleData* vehicle = VehicleService::findVehicle(licensePlate, vehicles);
    if (vehicle) {
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

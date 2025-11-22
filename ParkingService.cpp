#include "ParkingService.h"
#include "VehicleNotFoundError.h"
#include "SpotNotFoundError.h"
#include "SpotAlreadyOccupiedError.h"
#include "VehicleAlreadyParkedError.h"
#include "SpotAlreadyFreeError.h"
#include "IncompatibleSpotSizeError.h"
#include <algorithm>
#include <ranges>
#include <format>

bool ParkingService::parkVehicle(std::string_view licensePlate,  // Исправлено: string_view
                                 int lotId,
                                 int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 const std::vector<VehicleData>& vehicles) {
    auto vehicleIt = std::ranges::find_if(vehicles,  // Исправлено: ranges::find_if
                                          [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });

    if (vehicleIt == vehicles.end()) {
        throw VehicleNotFoundError(std::format("Vehicle with license plate {} not found", licensePlate));  // Исправлено: std::format
    }

    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        throw SpotNotFoundError(std::format("Parking lot with ID {} not found", lotId));  // Исправлено: std::format
    }

    ParkingSpotData* spot = findSpot(lotIt->second, spotNumber);
    if (!spot) {
        throw SpotNotFoundError(std::format("Parking spot {} not found", spotNumber));  // Исправлено: std::format
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
    spot->setVehicleLicensePlate(std::string(licensePlate));

    return true;
}

bool ParkingService::releaseSpot(int lotId,
                                 int spotNumber,
                                 std::map<int, ParkingLotData>& lots,
                                 std::vector<VehicleData>& vehicles) {
    auto lotIt = lots.find(lotId);
    if (lotIt == lots.end()) {
        throw SpotNotFoundError(std::format("Parking lot with ID {} not found", lotId));  // Исправлено: std::format
    }

    ParkingSpotData* spot = findSpot(lotIt->second, spotNumber);
    if (!spot) {
        throw SpotNotFoundError(std::format("Parking spot {} not found", spotNumber));  // Исправлено: std::format
    }

    if (!spot->isOccupied()) {
        throw SpotAlreadyFreeError();
    }

    std::string licensePlate = spot->getVehicleLicensePlate();
    spot->setOccupied(false);
    spot->setVehicleLicensePlate("");
    spot->clearParkingTime();

    if (auto vehicleIt = std::ranges::find_if(vehicles,  // Исправлено: init-statement
                                              [&licensePlate](const VehicleData& v) { return v.getLicensePlate() == licensePlate; });
        vehicleIt != vehicles.end()) {
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

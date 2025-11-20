#include "FilterCriteria.h"

bool FilterCriteria::matchesVehicle(const VehicleData& vehicle) const {
    if (!includeCars && vehicle.getType() == "Car") return false;
    if (!includeTrucks && vehicle.getType() == "Truck") return false;
    if (!includeParked && vehicle.isParked()) return false;
    if (!includeNotParked && !vehicle.isParked()) return false;
    return true;
}

bool FilterCriteria::matchesSpot(const ParkingSpotData& spot) const {
    if (spotSize != "All" && spot.getSizeString() != spotSize.toStdString()) {
        return false;
    }
    if (spot.getNumber() < minSpotNumber || spot.getNumber() > maxSpotNumber) {
        return false;
    }
    return true;
}

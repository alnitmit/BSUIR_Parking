#ifndef FILTERCRITERIA_H
#define FILTERCRITERIA_H

#include <QString>
#include "VehicleData.h"
#include "ParkingSpotData.h"

struct FilterCriteria {
    bool includeCars = true;
    bool includeTrucks = true;
    bool includeParked = true;
    bool includeNotParked = true;
    QString spotSize = "ALL";
    int minSpotNumber = 1;
    int maxSpotNumber = 1000;

    bool matchesVehicle(const VehicleData& vehicle) const;
    bool matchesSpot(const ParkingSpotData& spot) const;
};

#endif

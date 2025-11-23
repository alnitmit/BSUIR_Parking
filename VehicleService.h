#ifndef VEHICLESERVICE_H
#define VEHICLESERVICE_H

#include <vector>
#include <string>
#include "VehicleData.h"

class VehicleService {
public:
    static bool addVehicle(const VehicleData& vehicle, std::vector<VehicleData>& vehicles);
    static bool removeVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles);
    static VehicleData* findVehicle(const std::string& licensePlate, std::vector<VehicleData>& vehicles);
    static const VehicleData* findVehicle(const std::string& licensePlate, const std::vector<VehicleData>& vehicles);
    static bool isVehicleParked(const std::string& licensePlate, const std::vector<VehicleData>& vehicles);
};

#endif

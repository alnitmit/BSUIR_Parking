#ifndef PARKINGSERVICE_H
#define PARKINGSERVICE_H

#include <vector>
#include <map>
#include <memory>
#include <string>
#include "VehicleData.h"
#include "ParkingLotData.h"
#include "ParkingSpotData.h"

class ParkingService {
public:
    static bool parkVehicle(const std::string& licensePlate, 
                           int lotId, 
                           int spotNumber,
                           std::map<int, ParkingLotData>& lots,
                           const std::vector<VehicleData>& vehicles);
    
    static bool releaseSpot(int lotId, 
                           int spotNumber,
                           std::map<int, ParkingLotData>& lots,
                           std::vector<VehicleData>& vehicles);
    
    static bool isSpotCompatible(const VehicleData& vehicle, const ParkingSpotData& spot);
    
    static ParkingSpotData* findSpot(ParkingLotData& lot, int spotNumber);
    static const ParkingSpotData* findSpot(const ParkingLotData& lot, int spotNumber);
};

#endif


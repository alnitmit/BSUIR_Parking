#ifndef PARKINGLOTSERVICE_H
#define PARKINGLOTSERVICE_H

#include <map>
#include <string>
#include "ParkingLotData.h"
#include "ParkingSpotData.h"

class ParkingLotService {
public:
    static bool createParkingLot(const std::string& name, 
                                 int totalSpots, 
                                 int lotId,
                                 std::map<int, ParkingLotData>& lots);
    
    static bool removeParkingLot(int lotId, std::map<int, ParkingLotData>& lots);
    
    static ParkingLotData* getParkingLot(int lotId, std::map<int, ParkingLotData>& lots);
    static const ParkingLotData* getParkingLot(int lotId, const std::map<int, ParkingLotData>& lots);
    
    static int getOccupiedSpots(const ParkingLotData& lot);
    static int getFreeSpots(const ParkingLotData& lot);
    static double getOccupancyRate(const ParkingLotData& lot);
    
private:
    static void initializeSpots(ParkingLotData& lot, int totalSpots);
};

#endif


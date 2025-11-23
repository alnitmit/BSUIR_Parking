#ifndef PARKINGLOTSERVICE_H
#define PARKINGLOTSERVICE_H

#include <map>
#include <string>
#include <string_view>
#include "ParkingLotData.h"
#include "ParkingSpotData.h"

class ParkingLotService {
public:
    static bool createParkingLot(std::string_view name,
                                 int totalSpots,
                                 int& nextLotId,
                                 std::map<int, ParkingLotData>& lots);

    static bool removeParkingLot(int lotId, std::map<int, ParkingLotData>& lots);

    static ParkingLotData* getParkingLot(int lotId, std::map<int, ParkingLotData>& lots);
    static const ParkingLotData* getParkingLot(int lotId, const std::map<int, ParkingLotData>& lots);

    static int getOccupiedSpots(const ParkingLotData& lot);
    static int getFreeSpots(const ParkingLotData& lot);
    static double getOccupancyRate(const ParkingLotData& lot);
};

#endif

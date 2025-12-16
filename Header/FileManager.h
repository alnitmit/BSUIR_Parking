#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <map>
#include "VehicleData.h"
#include "ParkingLotData.h"

class FileManager {
public:
    static bool saveSystemState(const std::vector<VehicleData>& vehicles,
                                const std::map<int, ParkingLotData>& parkingLots,
                                int nextLotId);
    static bool loadSystemState(std::vector<VehicleData>& vehicles,
                                std::map<int, ParkingLotData>& parkingLots,
                                int& nextLotId);
};

#endif

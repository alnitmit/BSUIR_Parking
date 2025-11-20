#include "ParkingLotService.h"
#include <algorithm>

bool ParkingLotService::createParkingLot(const std::string& name, 
                                          int totalSpots, 
                                          int lotId,
                                          std::map<int, ParkingLotData>& lots) {
    if (totalSpots > 40) totalSpots = 40;
    
    ParkingLotData lot(lotId, name);
    initializeSpots(lot, totalSpots);
    
    lots[lotId] = lot;
    return true;
}

bool ParkingLotService::removeParkingLot(int lotId, std::map<int, ParkingLotData>& lots) {
    auto it = lots.find(lotId);
    if (it != lots.end()) {
        lots.erase(it);
        return true;
    }
    return false;
}

ParkingLotData* ParkingLotService::getParkingLot(int lotId, std::map<int, ParkingLotData>& lots) {
    auto it = lots.find(lotId);
    return (it != lots.end()) ? &it->second : nullptr;
}

const ParkingLotData* ParkingLotService::getParkingLot(int lotId, const std::map<int, ParkingLotData>& lots) {
    auto it = lots.find(lotId);
    return (it != lots.end()) ? &it->second : nullptr;
}

int ParkingLotService::getOccupiedSpots(const ParkingLotData& lot) {
    return std::count_if(lot.getSpots().begin(), lot.getSpots().end(),
        [](const ParkingSpotData& s) { return s.isOccupied(); });
}

int ParkingLotService::getFreeSpots(const ParkingLotData& lot) {
    return static_cast<int>(lot.getSpots().size()) - getOccupiedSpots(lot);
}

double ParkingLotService::getOccupancyRate(const ParkingLotData& lot) {
    if (lot.getSpots().empty()) return 0.0;
    return static_cast<double>(getOccupiedSpots(lot)) / lot.getSpots().size() * 100.0;
}

void ParkingLotService::initializeSpots(ParkingLotData& lot, int totalSpots) {
    lot.clearSpots();
    
    int compactSpots = std::max(1, totalSpots / 3);
    int largeSpots = std::max(1, totalSpots / 4);
    int standardSpots = totalSpots - compactSpots - largeSpots;
    
    int spotNumber = 1;
    
    for (int i = 0; i < compactSpots; ++i) {
        ParkingSpotData spot(spotNumber++, ParkingSpotData::Size::COMPACT);
        lot.addSpot(spot);
    }
    
    for (int i = 0; i < standardSpots; ++i) {
        ParkingSpotData spot(spotNumber++, ParkingSpotData::Size::STANDARD);
        lot.addSpot(spot);
    }
    
    for (int i = 0; i < largeSpots; ++i) {
        ParkingSpotData spot(spotNumber++, ParkingSpotData::Size::LARGE);
        lot.addSpot(spot);
    }
}

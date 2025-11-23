#include "ParkingLotService.h"
#include "ParkingSpotData.h"
#include <algorithm>
#include <ranges>

bool ParkingLotService::createParkingLot(std::string_view name, int totalSpots, int& nextLotId, std::map<int, ParkingLotData>& lots) {
    if (name.empty() || totalSpots <= 0) {
        return false;
    }

    for (const auto& [id, lot] : lots) {
        if (lot.getName() == name) {
            return false;
        }
    }

    int lotId = nextLotId;
    nextLotId++;

    ParkingLotData newLot(lotId, name);

    for (int i = 1; i <= totalSpots; ++i) {
        // Используем полные имена вместо using enum
        ParkingSpotData::Size spotSize = ParkingSpotData::Size::Standard;
        if (i <= totalSpots * 0.2) {
            spotSize = ParkingSpotData::Size::Compact;
        } else if (i > totalSpots * 0.8) {
            spotSize = ParkingSpotData::Size::Large;
        }

        ParkingSpotData spot(i, spotSize);
        newLot.addSpot(spot);
    }

    lots[lotId] = newLot;
    return true;
}

bool ParkingLotService::removeParkingLot(int lotId, std::map<int, ParkingLotData>& lots) {
    return lots.erase(lotId) > 0;
}

ParkingLotData* ParkingLotService::getParkingLot(int lotId, std::map<int, ParkingLotData>& lots) {
    auto it = lots.find(lotId);
    return it != lots.end() ? &it->second : nullptr;
}

const ParkingLotData* ParkingLotService::getParkingLot(int lotId, const std::map<int, ParkingLotData>& lots) {
    auto it = lots.find(lotId);
    return it != lots.end() ? &it->second : nullptr;
}

int ParkingLotService::getOccupiedSpots(const ParkingLotData& lot) {
    return std::ranges::count_if(lot.getSpots(),
                                 [](const ParkingSpotData& spot) { return spot.isOccupied(); });
}

int ParkingLotService::getFreeSpots(const ParkingLotData& lot) {
    return static_cast<int>(lot.getSpots().size()) - getOccupiedSpots(lot);
}

double ParkingLotService::getOccupancyRate(const ParkingLotData& lot) {
    auto total = static_cast<int>(lot.getSpots().size());
    if (total == 0) return 0.0;

    auto occupied = getOccupiedSpots(lot);
    return (static_cast<double>(occupied) / total) * 100.0;
}

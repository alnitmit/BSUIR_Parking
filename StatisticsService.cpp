#include "StatisticsService.h"
#include <algorithm>
#include <ranges>

ParkingStatistics::ParkingStatistics()  // Исправлено: инициализация в классе
{}

int ParkingStatistics::getTotalSpots() const {
    return totalSpots_;
}

void ParkingStatistics::setTotalSpots(int totalSpots) {
    totalSpots_ = totalSpots;
}

int ParkingStatistics::getOccupiedSpots() const {
    return occupiedSpots_;
}

void ParkingStatistics::setOccupiedSpots(int occupiedSpots) {
    occupiedSpots_ = occupiedSpots;
}

int ParkingStatistics::getFreeSpots() const {
    return freeSpots_;
}

void ParkingStatistics::setFreeSpots(int freeSpots) {
    freeSpots_ = freeSpots;
}

double ParkingStatistics::getOccupancyRate() const {
    return occupancyRate_;
}

void ParkingStatistics::setOccupancyRate(double occupancyRate) {
    occupancyRate_ = occupancyRate;
}

ParkingStatistics StatisticsService::calculateStatistics(const std::map<int, ParkingLotData>& lots) {
    ParkingStatistics stats;

    int totalSpots = 0;
    int occupiedSpots = 0;

    for (const auto& [id, lot] : lots) {
        totalSpots += static_cast<int>(lot.getSpots().size());
        occupiedSpots += std::ranges::count_if(lot.getSpots(),  // Исправлено: ranges::count_if
                                               [](const ParkingSpotData& s) { return s.isOccupied(); });
    }

    stats.setTotalSpots(totalSpots);
    stats.setOccupiedSpots(occupiedSpots);
    stats.setFreeSpots(totalSpots - occupiedSpots);

    double rate = (totalSpots > 0)
                      ? static_cast<double>(occupiedSpots) / totalSpots * 100.0
                      : 0.0;
    stats.setOccupancyRate(rate);

    return stats;
}

int StatisticsService::getTotalSpots(const std::map<int, ParkingLotData>& lots) {
    int total = 0;
    for (const auto& [id, lot] : lots) {
        total += static_cast<int>(lot.getSpots().size());
    }
    return total;
}

int StatisticsService::getOccupiedSpots(const std::map<int, ParkingLotData>& lots) {
    int occupied = 0;
    for (const auto& [id, lot] : lots) {
        occupied += std::ranges::count_if(lot.getSpots(),  // Исправлено: ranges::count_if
                                          [](const ParkingSpotData& s) { return s.isOccupied(); });
    }
    return occupied;
}

int StatisticsService::getFreeSpots(const std::map<int, ParkingLotData>& lots) {
    return getTotalSpots(lots) - getOccupiedSpots(lots);
}

double StatisticsService::getOccupancyRate(const std::map<int, ParkingLotData>& lots) {
    int total = getTotalSpots(lots);
    if (total == 0) return 0.0;
    return static_cast<double>(getOccupiedSpots(lots)) / total * 100.0;
}

#ifndef STATISTICSSERVICE_H
#define STATISTICSSERVICE_H

#include <map>
#include "ParkingLotData.h"

class ParkingStatistics {
public:
    ParkingStatistics();

    int getTotalSpots() const;
    void setTotalSpots(int totalSpots);

    int getOccupiedSpots() const;
    void setOccupiedSpots(int occupiedSpots);

    int getFreeSpots() const;
    void setFreeSpots(int freeSpots);

    double getOccupancyRate() const;
    void setOccupancyRate(double occupancyRate);

private:
    int totalSpots_ = 0;  // Исправлено: инициализация в классе
    int occupiedSpots_ = 0;
    int freeSpots_ = 0;
    double occupancyRate_ = 0.0;
};

class StatisticsService {
public:
    static ParkingStatistics calculateStatistics(const std::map<int, ParkingLotData>& lots);
    static int getTotalSpots(const std::map<int, ParkingLotData>& lots);
    static int getOccupiedSpots(const std::map<int, ParkingLotData>& lots);
    static int getFreeSpots(const std::map<int, ParkingLotData>& lots);
    static double getOccupancyRate(const std::map<int, ParkingLotData>& lots);
};

#endif

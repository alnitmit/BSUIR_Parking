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
    int totalSpots_;
    int occupiedSpots_;
    int freeSpots_;
    double occupancyRate_;
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

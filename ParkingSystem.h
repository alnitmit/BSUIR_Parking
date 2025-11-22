#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <vector>
#include <map>
#include <string>
#include "VehicleData.h"
#include "ParkingLotData.h"

class ParkingSystem {
public:
    ParkingSystem();
    ~ParkingSystem();

    // Удаление копирования и перемещения
    ParkingSystem(const ParkingSystem&) = delete;
    ParkingSystem& operator=(const ParkingSystem&) = delete;
    ParkingSystem(ParkingSystem&&) = delete;
    ParkingSystem& operator=(ParkingSystem&&) = delete;

    bool addVehicle(const VehicleData& vehicle);
    bool removeVehicle(const std::string& licensePlate);
    VehicleData* findVehicle(const std::string& licensePlate);
    const VehicleData* findVehicle(const std::string& licensePlate) const;

    bool createParkingLot(const std::string& name, int totalSpots);
    bool removeParkingLot(int lotId);
    ParkingLotData* getParkingLot(int lotId);
    const ParkingLotData* getParkingLot(int lotId) const;

    bool parkVehicle(const std::string& licensePlate, int lotId, int spotNumber);
    bool releaseSpot(int lotId, int spotNumber);

    const std::vector<VehicleData>& getVehicles() const;
    const std::map<int, ParkingLotData>& getParkingLots() const;

    int getTotalSpots() const;
    int getOccupiedSpots() const;
    int getFreeSpots() const;
    double getOccupancyRate() const;

    bool saveState() const;  // Исправлено: const
    bool loadState() const;  // Исправлено: const

private:
    void initializeDefaultLots();
};

#endif

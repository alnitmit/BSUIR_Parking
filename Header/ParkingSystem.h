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

    ParkingSystem(const ParkingSystem&) = delete;
    ParkingSystem& operator=(const ParkingSystem&) = delete;
    ParkingSystem(ParkingSystem&&) = delete;
    ParkingSystem& operator=(ParkingSystem&&) = delete;

    bool addVehicle(const VehicleData& vehicle) const;
    bool removeVehicle(const std::string& licensePlate) const;
    VehicleData* findVehicle(const std::string& licensePlate);
    const VehicleData* findVehicle(const std::string& licensePlate) const;

    bool createParkingLot(const std::string& name, int totalSpots) const;
    bool removeParkingLot(int lotId) const;
    ParkingLotData* getParkingLot(int lotId);
    const ParkingLotData* getParkingLot(int lotId) const;

    bool parkVehicle(const std::string& licensePlate, int lotId, int spotNumber) const;
    bool releaseSpot(int lotId, int spotNumber) const;

    const std::vector<VehicleData>& getVehicles() const;
    const std::map<int, ParkingLotData>& getParkingLots() const;

    int getTotalSpots() const;
    int getOccupiedSpots() const;
    int getFreeSpots() const;
    double getOccupancyRate() const;

    bool saveState() const;
    bool loadState() const;

private:
    void initializeDefaultLots() const;
};

#endif

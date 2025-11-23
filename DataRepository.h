#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <vector>
#include <map>
#include <string>
#include "VehicleData.h"
#include "ParkingLotData.h"

class DataRepository {
public:
    static DataRepository& getInstance() {
        static DataRepository instance;
        return instance;
    }

    std::vector<VehicleData>& getVehicles() { return vehicles_; }
    const std::vector<VehicleData>& getVehicles() const { return vehicles_; }
    std::map<int, ParkingLotData>& getParkingLots() { return lots_; }
    const std::map<int, ParkingLotData>& getParkingLots() const { return lots_; }

    int& getNextLotId() { return nextLotId_; }
    int getNextLotId() const { return nextLotId_; }
    void setNextLotId(int id) const { nextLotId_ = id; } // Убрано const

    void clear();

private:
    DataRepository() = default;
    ~DataRepository() = default;
    DataRepository(const DataRepository&) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    std::vector<VehicleData> vehicles_;
    std::map<int, ParkingLotData> lots_;
    inline static int nextLotId_ = 1; // Уже правильно как inline variable
};

#endif

#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <vector>
#include <map>
#include <string>
#include "VehicleData.h"
#include "ParkingLotData.h"

class DataRepository {
public:
    // Используем статическую локальную переменную - это стандартный и рабочий подход
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

    void resetNextLotId() { nextLotId_ = 1; }

    void clear();

    // Удаляем конструкторы копирования и присваивания
    DataRepository(const DataRepository&) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

private:
    DataRepository() = default;
    ~DataRepository() = default;

    std::vector<VehicleData> vehicles_;
    std::map<int, ParkingLotData> lots_;
    int nextLotId_ = 1;
};

#endif

#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <vector>
#include <map>
#include <string>
#include "VehicleData.h"
#include "ParkingLotData.h"

class DataRepository {
private:
    inline static DataRepository* instance = nullptr;

public:
    static DataRepository& getInstance() {
        if (!instance) {
            instance = new DataRepository();
        }
        return *instance;
    }

    static void destroyInstance() {
        delete instance;
        instance = nullptr;
    }

    std::vector<VehicleData>& getVehicles() { return vehicles_; }
    const std::vector<VehicleData>& getVehicles() const { return vehicles_; }
    std::map<int, ParkingLotData>& getParkingLots() { return lots_; }
    const std::map<int, ParkingLotData>& getParkingLots() const { return lots_; }

    // Убираем сеттер и предоставляем доступ через метод, который логически оправдан
    int& getNextLotId() { return nextLotId_; }
    int getNextLotId() const { return nextLotId_; }

    // Вместо сеттера используем метод с осмысленным именем
    void resetNextLotId() { nextLotId_ = 1; }

    void clear();

private:
    DataRepository() = default;
    ~DataRepository() = default;
    DataRepository(const DataRepository&) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    std::vector<VehicleData> vehicles_;
    std::map<int, ParkingLotData> lots_;
    int nextLotId_ = 1;
};

#endif

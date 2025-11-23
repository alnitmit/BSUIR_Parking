#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <vector>
#include <map>
#include <string>
#include "VehicleData.h"
#include "ParkingLotData.h"

class DataRepository {
private:
    inline static DataRepository* instance = nullptr;  // Inline variable вместо локального static

public:
    static DataRepository& getInstance() {
        if (!instance) {
            instance = new DataRepository();
        }
        return *instance;
    }

    static void destroyInstance() {  // Добавляем метод для очистки
        delete instance;
        instance = nullptr;
    }

    std::vector<VehicleData>& getVehicles() { return vehicles_; }
    const std::vector<VehicleData>& getVehicles() const { return vehicles_; }
    std::map<int, ParkingLotData>& getParkingLots() { return lots_; }
    const std::map<int, ParkingLotData>& getParkingLots() const { return lots_; }

    int& getNextLotId() { return nextLotId_; }
    int getNextLotId() const { return nextLotId_; }

    void setNextLotId(int id) const {
        const_cast<DataRepository*>(this)->nextLotId_ = id;
    }

    void clear();

private:
    DataRepository() = default;
    ~DataRepository() = default;
    DataRepository(const DataRepository&) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    std::vector<VehicleData> vehicles_;
    std::map<int, ParkingLotData> lots_;
    mutable int nextLotId_ = 1;
};

#endif

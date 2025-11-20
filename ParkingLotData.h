#ifndef PARKINGLOTDATA_H
#define PARKINGLOTDATA_H

#include <vector>
#include <string>
#include "ParkingSpotData.h"

class ParkingLotData {
public:
    ParkingLotData();
    ParkingLotData(int id, const std::string& name);
    
    int getId() const;
    void setId(int id);
    
    std::string getName() const;
    void setName(const std::string& name);
    
    std::vector<ParkingSpotData>& getSpots();
    const std::vector<ParkingSpotData>& getSpots() const;
    
    void addSpot(const ParkingSpotData& spot);
    void clearSpots();

private:
    int id_;
    std::string name_;
    std::vector<ParkingSpotData> spots_;
};

#endif

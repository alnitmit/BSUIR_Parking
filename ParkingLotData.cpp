#include "ParkingLotData.h"
#include <algorithm>

ParkingLotData::ParkingLotData() : id_(0) {}

ParkingLotData::ParkingLotData(int id, const std::string& name) : id_(id), name_(name) {}

int ParkingLotData::getId() const { return id_; }
void ParkingLotData::setId(int id) { id_ = id; }

std::string ParkingLotData::getName() const { return name_; }  // Исправлено
void ParkingLotData::setName(const std::string& name) {
    name_ = name;
}

std::vector<ParkingSpotData>& ParkingLotData::getSpots() { return spots_; }
const std::vector<ParkingSpotData>& ParkingLotData::getSpots() const { return spots_; }

void ParkingLotData::addSpot(const ParkingSpotData& spot) {
    spots_.push_back(spot);
}

void ParkingLotData::clearSpots() {
    spots_.clear();
}

void ParkingLotData::removeSpot(int spotNumber) {
    auto it = std::find_if(spots_.begin(), spots_.end(),
                           [spotNumber](const ParkingSpotData& spot) {
                               return spot.getNumber() == spotNumber;
                           });

    if (it != spots_.end()) {
        spots_.erase(it);
    }
}

ParkingSpotData* ParkingLotData::getSpot(int spotNumber) {
    auto it = std::find_if(spots_.begin(), spots_.end(),
                           [spotNumber](const ParkingSpotData& spot) {
                               return spot.getNumber() == spotNumber;
                           });

    return it != spots_.end() ? &(*it) : nullptr;
}

const ParkingSpotData* ParkingLotData::getSpot(int spotNumber) const {
    auto it = std::find_if(spots_.begin(), spots_.end(),
                           [spotNumber](const ParkingSpotData& spot) {
                               return spot.getNumber() == spotNumber;
                           });

    return it != spots_.end() ? &(*it) : nullptr;
}

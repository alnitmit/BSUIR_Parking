#include "ParkingLotData.h"
#include <algorithm>
#include <ranges>
#include <memory>

ParkingLotData::ParkingLotData() : id_(0) {}

ParkingLotData::ParkingLotData(int id, std::string_view name) : id_(id), name_(name) {}

int ParkingLotData::getId() const { return id_; }
void ParkingLotData::setId(int id) { id_ = id; }

std::string ParkingLotData::getName() const { return name_; }
void ParkingLotData::setName(std::string_view name) {
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
    if (auto it = std::ranges::find_if(spots_,
                                       [spotNumber](const ParkingSpotData& spot) {
                                           return spot.getNumber() == spotNumber;
                                       }); it != spots_.end()) {
        spots_.erase(it);
    }
}

ParkingSpotData* ParkingLotData::getSpot(int spotNumber) {
    if (auto it = std::ranges::find_if(spots_,
                                       [spotNumber](const ParkingSpotData& spot) {
                                           return spot.getNumber() == spotNumber;
                                       }); it != spots_.end()) {
        return std::to_address(it);
    }
    return nullptr;
}

const ParkingSpotData* ParkingLotData::getSpot(int spotNumber) const {
    if (auto it = std::ranges::find_if(spots_,
                                       [spotNumber](const ParkingSpotData& spot) {
                                           return spot.getNumber() == spotNumber;
                                       }); it != spots_.end()) {
        return std::to_address(it);
    }
    return nullptr;
}

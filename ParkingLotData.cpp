#include "ParkingLotData.h"
#include <string_view>

ParkingLotData::ParkingLotData() : id_(0) {}

ParkingLotData::ParkingLotData(int id, std::string_view name) : id_(id), name_(name) {}  // Исправлено: string_view

int ParkingLotData::getId() const {
    return id_;
}

void ParkingLotData::setId(int id) {
    id_ = id;
}

std::string ParkingLotData::getName() const {
    return name_;
}

void ParkingLotData::setName(std::string_view name) {  // Исправлено: string_view
    name_ = name;
}

std::vector<ParkingSpotData>& ParkingLotData::getSpots() {
    return spots_;
}

const std::vector<ParkingSpotData>& ParkingLotData::getSpots() const {
    return spots_;
}

void ParkingLotData::addSpot(const ParkingSpotData& spot) {
    spots_.push_back(spot);
}

void ParkingLotData::clearSpots() {
    spots_.clear();
}

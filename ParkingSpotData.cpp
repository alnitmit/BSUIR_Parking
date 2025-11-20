#include "ParkingSpotData.h"

ParkingSpotData::ParkingSpotData() : number_(0), size_(Size::STANDARD), occupied_(false) {}

ParkingSpotData::ParkingSpotData(int number, Size size) 
    : number_(number), size_(size), occupied_(false) {}

int ParkingSpotData::getNumber() const {
    return number_;
}

void ParkingSpotData::setNumber(int number) {
    number_ = number;
}

ParkingSpotData::Size ParkingSpotData::getSize() const {
    return size_;
}

void ParkingSpotData::setSize(Size size) {
    size_ = size;
}

std::string ParkingSpotData::getSizeString() const {
    switch (size_) {
    case Size::COMPACT: return "Компактное";
    case Size::STANDARD: return "Стандартное";
    case Size::LARGE: return "Большое";
    default: return "Неизвестно";
    }
}

bool ParkingSpotData::isOccupied() const {
    return occupied_;
}

void ParkingSpotData::setOccupied(bool occupied) {
    occupied_ = occupied;
}

std::string ParkingSpotData::getVehicleLicensePlate() const {
    return vehicleLicensePlate_;
}

void ParkingSpotData::setVehicleLicensePlate(const std::string& licensePlate) {
    vehicleLicensePlate_ = licensePlate;
}

std::optional<std::string> ParkingSpotData::getParkingTime() const {
    return parkingTime_;
}

void ParkingSpotData::setParkingTime(const std::optional<std::string>& time) {
    parkingTime_ = time;
}

void ParkingSpotData::clearParkingTime() {
    parkingTime_.reset();
}

ParkingSpotData::Size ParkingSpotData::parseSize(const std::string& str) {
    if (str == "COMPACT") return Size::COMPACT;
    if (str == "STANDARD") return Size::STANDARD;
    if (str == "LARGE") return Size::LARGE;
    return Size::STANDARD;
}

#include "ParkingSpotData.h"

using enum ParkingSpotData::Size;  // Исправлено: using enum

ParkingSpotData::ParkingSpotData() : number_(0), size_(STANDARD) {}  // Исправлено: using enum

ParkingSpotData::ParkingSpotData(int number, Size size)
    : number_(number), size_(size) {}

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
    case COMPACT: return "COMPACT";  // Исправлено: using enum
    case STANDARD: return "STANDARD";
    case LARGE: return "LARGE";
    default: return "STANDARD";
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

void ParkingSpotData::setVehicleLicensePlate(std::string_view licensePlate) {
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

ParkingSpotData::Size ParkingSpotData::parseSize(std::string_view str) {
    if (str == "COMPACT") return COMPACT;  // Исправлено: using enum
    if (str == "STANDARD") return STANDARD;
    if (str == "LARGE") return LARGE;
    return STANDARD;
}

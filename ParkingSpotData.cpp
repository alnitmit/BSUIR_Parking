#include "ParkingSpotData.h"
#include <stdexcept>

ParkingSpotData::ParkingSpotData() : number_(0), size_(Size::Standard), occupied_(false) {}

ParkingSpotData::ParkingSpotData(int number, Size size)
    : number_(number), size_(size), occupied_(false) {}

int ParkingSpotData::getNumber() const { return number_; }
void ParkingSpotData::setNumber(int number) { number_ = number; }

ParkingSpotData::Size ParkingSpotData::getSize() const { return size_; }
void ParkingSpotData::setSize(Size size) { size_ = size; }

bool ParkingSpotData::isOccupied() const { return occupied_; }
void ParkingSpotData::setOccupied(bool occupied) { occupied_ = occupied; }

std::string ParkingSpotData::getVehicleLicensePlate() const { return vehicleLicensePlate_; }  // Исправлено
void ParkingSpotData::setVehicleLicensePlate(const std::string& licensePlate) {
    vehicleLicensePlate_ = licensePlate;
}

void ParkingSpotData::occupy(const std::string& licensePlate) {
    if (occupied_) {
        throw std::runtime_error("Spot already occupied");
    }
    occupied_ = true;
    vehicleLicensePlate_ = licensePlate;
}

void ParkingSpotData::release() {
    if (!occupied_) {
        throw std::runtime_error("Spot already free");
    }
    occupied_ = false;
    vehicleLicensePlate_.clear();
}

std::string ParkingSpotData::getSizeString() const {
    return sizeToString(size_);
}

ParkingSpotData::Size ParkingSpotData::parseSize(const std::string& str) {
    if (str == "Compact") return Size::Compact;
    if (str == "Standard") return Size::Standard;
    if (str == "Large") return Size::Large;
    throw std::invalid_argument("Invalid spot size");
}

std::string ParkingSpotData::sizeToString(Size size) {
    switch (size) {
    case Size::Compact: return "Compact";
    case Size::Standard: return "Standard";
    case Size::Large: return "Large";
    default: return "Unknown";
    }
}

// Реализация остальных методов
std::optional<std::string> ParkingSpotData::getParkingTime() const { return parkingTime_; }
void ParkingSpotData::setParkingTime(const std::optional<std::string>& time) { parkingTime_ = time; }
void ParkingSpotData::clearParkingTime() { parkingTime_.reset(); }

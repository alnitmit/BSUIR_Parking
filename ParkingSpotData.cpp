#include "ParkingSpotData.h"
#include <stdexcept>
#include "SpotAlreadyOccupiedError.h"
#include "SpotAlreadyFreeError.h"

ParkingSpotData::ParkingSpotData() : number_(0), size_(Size::Standard) {}

ParkingSpotData::ParkingSpotData(int number, Size size)
    : number_(number), size_(size) {}

int ParkingSpotData::getNumber() const { return number_; }
void ParkingSpotData::setNumber(int number) { number_ = number; }

ParkingSpotData::Size ParkingSpotData::getSize() const { return size_; }
void ParkingSpotData::setSize(Size size) { size_ = size; }

bool ParkingSpotData::isOccupied() const { return occupied_; }
void ParkingSpotData::setOccupied(bool occupied) { occupied_ = occupied; }

std::string ParkingSpotData::getVehicleLicensePlate() const { return vehicleLicensePlate_; }
void ParkingSpotData::setVehicleLicensePlate(std::string_view licensePlate) {
    vehicleLicensePlate_ = licensePlate;
}

void ParkingSpotData::occupy(std::string_view licensePlate) {
    if (occupied_) {
        throw SpotAlreadyOccupiedError("Spot already occupied");
    }
    occupied_ = true;
    vehicleLicensePlate_ = licensePlate;
}

void ParkingSpotData::release() {
    if (!occupied_) {
        throw SpotAlreadyFreeError("Spot already free");
    }
    occupied_ = false;
    vehicleLicensePlate_.clear();
}

std::string ParkingSpotData::getSizeString() const {
    using enum Size;
    switch (size_) {
    case Compact: return "Компактное";
    case Standard: return "Стандартное";
    case Large: return "Большое";
    default: return "Неизвестное";
    }
}

ParkingSpotData::Size ParkingSpotData::parseSize(std::string_view str) {
    using enum Size;
    if (str == "Compact") return Compact;
    if (str == "Standard") return Standard;
    if (str == "Large") return Large;
    throw std::invalid_argument("Invalid spot size");
}

std::string ParkingSpotData::sizeToString(Size size) {
    using enum Size;
    switch (size) {
    case Compact: return "Компактное";
    case Standard: return "Стандартное";
    case Large: return "Большое";
    default: return "Неизвестное";
    }
}

std::optional<std::string> ParkingSpotData::getParkingTime() const { return parkingTime_; }
void ParkingSpotData::setParkingTime(const std::optional<std::string>& time) { parkingTime_ = time; }
void ParkingSpotData::clearParkingTime() { parkingTime_.reset(); }

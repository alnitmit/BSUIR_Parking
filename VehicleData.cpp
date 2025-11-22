#include "VehicleData.h"
#include <string_view>

VehicleData::VehicleData(std::string_view type, std::string_view model, std::string_view licensePlate)  // Исправлено: string_view
    : type_(type), model_(model), licensePlate_(licensePlate) {}

std::string VehicleData::getType() const {
    return type_;
}

void VehicleData::setType(std::string_view type) {  // Исправлено: string_view
    type_ = type;
}

std::string VehicleData::getModel() const {
    return model_;
}

void VehicleData::setModel(std::string_view model) {  // Исправлено: string_view
    model_ = model;
}

std::string VehicleData::getLicensePlate() const {
    return licensePlate_;
}

void VehicleData::setLicensePlate(std::string_view licensePlate) {  // Исправлено: string_view
    licensePlate_ = licensePlate;
}

bool VehicleData::isParked() const {
    return isParked_;
}

void VehicleData::setParked(bool parked) {
    isParked_ = parked;
}

std::string VehicleData::getCargoType() const {
    return cargoType_;
}

void VehicleData::setCargoType(std::string_view cargoType) {  // Исправлено: string_view
    cargoType_ = cargoType;
}

#include "VehicleData.h"

VehicleData::VehicleData() : isParked_(false) {}

VehicleData::VehicleData(const std::string& type, const std::string& model, const std::string& licensePlate)
    : type_(type), model_(model), licensePlate_(licensePlate), isParked_(false) {}

std::string VehicleData::getType() const {
    return type_;
}

void VehicleData::setType(const std::string& type) {
    type_ = type;
}

std::string VehicleData::getModel() const {
    return model_;
}

void VehicleData::setModel(const std::string& model) {
    model_ = model;
}

std::string VehicleData::getLicensePlate() const {
    return licensePlate_;
}

void VehicleData::setLicensePlate(const std::string& licensePlate) {
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

void VehicleData::setCargoType(const std::string& cargoType) {
    cargoType_ = cargoType;
}


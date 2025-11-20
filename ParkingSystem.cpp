#include "ParkingSystem.h"
#include "DataRepository.h"
#include "ParkingService.h"
#include "VehicleService.h"
#include "ParkingLotService.h"
#include "StatisticsService.h"
#include "FileManager.h"
#include "VehicleNotFoundError.h"
#include "SpotNotFoundError.h"
#include "SpotAlreadyOccupiedError.h"
#include "VehicleAlreadyParkedError.h"
#include "SpotAlreadyFreeError.h"
#include "IncompatibleSpotSizeError.h"
#include "DuplicateVehicleError.h"

ParkingSystem::ParkingSystem() {
    loadState();
    auto& repo = DataRepository::getInstance();
    if (repo.getParkingLots().empty()) {
        initializeDefaultLots();
    }
}

ParkingSystem::~ParkingSystem() {
    saveState();
}

bool ParkingSystem::addVehicle(const VehicleData& vehicle) {
    auto& repo = DataRepository::getInstance();
    try {
        bool result = VehicleService::addVehicle(vehicle, repo.getVehicles());
        if (result) {
            saveState();
        }
        return result;
    } catch (const DuplicateVehicleError&) {
        return false;
    }
}

bool ParkingSystem::removeVehicle(const std::string& licensePlate) {
    auto& repo = DataRepository::getInstance();
    
    for (auto& [lotId, lot] : repo.getParkingLots()) {
        for (auto& spot : lot.getSpots()) {
            if (spot.isOccupied() && spot.getVehicleLicensePlate() == licensePlate) {
                spot.setOccupied(false);
                spot.setVehicleLicensePlate("");
                spot.clearParkingTime();
            }
        }
    }
    
    bool removed = VehicleService::removeVehicle(licensePlate, repo.getVehicles());
    if (removed) {
        saveState();
    }
    return removed;
}

VehicleData* ParkingSystem::findVehicle(const std::string& licensePlate) {
    auto& repo = DataRepository::getInstance();
    return VehicleService::findVehicle(licensePlate, repo.getVehicles());
}

const VehicleData* ParkingSystem::findVehicle(const std::string& licensePlate) const {
    const auto& repo = DataRepository::getInstance();
    return VehicleService::findVehicle(licensePlate, repo.getVehicles());
}

bool ParkingSystem::createParkingLot(const std::string& name, int totalSpots) {
    auto& repo = DataRepository::getInstance();
    int lotId = repo.getNextLotId()++;
    bool result = ParkingLotService::createParkingLot(name, totalSpots, lotId, repo.getParkingLots());
    if (result) {
        saveState();
    }
    return result;
}

bool ParkingSystem::removeParkingLot(int lotId) {
    auto& repo = DataRepository::getInstance();
    bool result = ParkingLotService::removeParkingLot(lotId, repo.getParkingLots());
    if (result) {
        saveState();
    }
    return result;
}

ParkingLotData* ParkingSystem::getParkingLot(int lotId) {
    auto& repo = DataRepository::getInstance();
    return ParkingLotService::getParkingLot(lotId, repo.getParkingLots());
}

const ParkingLotData* ParkingSystem::getParkingLot(int lotId) const {
    const auto& repo = DataRepository::getInstance();
    return ParkingLotService::getParkingLot(lotId, repo.getParkingLots());
}

bool ParkingSystem::parkVehicle(const std::string& licensePlate, int lotId, int spotNumber) {
    auto& repo = DataRepository::getInstance();
    bool result = ParkingService::parkVehicle(licensePlate, lotId, spotNumber, 
                                               repo.getParkingLots(), repo.getVehicles());
    if (result) {
        VehicleData* vehicle = findVehicle(licensePlate);
        if (vehicle) {
            vehicle->setParked(true);
        }
        saveState();
    }
    return result;
}

bool ParkingSystem::releaseSpot(int lotId, int spotNumber) {
    auto& repo = DataRepository::getInstance();
    bool result = ParkingService::releaseSpot(lotId, spotNumber, 
                                               repo.getParkingLots(), repo.getVehicles());
    if (result) {
        saveState();
    }
    return result;
}

const std::vector<VehicleData>& ParkingSystem::getVehicles() const {
    const auto& repo = DataRepository::getInstance();
    return repo.getVehicles();
}

const std::map<int, ParkingLotData>& ParkingSystem::getParkingLots() const {
    const auto& repo = DataRepository::getInstance();
    return repo.getParkingLots();
}

int ParkingSystem::getTotalSpots() const {
    const auto& repo = DataRepository::getInstance();
    return StatisticsService::getTotalSpots(repo.getParkingLots());
}

int ParkingSystem::getOccupiedSpots() const {
    const auto& repo = DataRepository::getInstance();
    return StatisticsService::getOccupiedSpots(repo.getParkingLots());
}

int ParkingSystem::getFreeSpots() const {
    const auto& repo = DataRepository::getInstance();
    return StatisticsService::getFreeSpots(repo.getParkingLots());
}

double ParkingSystem::getOccupancyRate() const {
    const auto& repo = DataRepository::getInstance();
    return StatisticsService::getOccupancyRate(repo.getParkingLots());
}

bool ParkingSystem::saveState() {
    const auto& repo = DataRepository::getInstance();
    return FileManager::saveSystemState(repo.getVehicles(), repo.getParkingLots(), repo.getNextLotId());
}

bool ParkingSystem::loadState() {
    auto& repo = DataRepository::getInstance();
    return FileManager::loadSystemState(repo.getVehicles(), repo.getParkingLots(), repo.getNextLotId());
}

void ParkingSystem::initializeDefaultLots() {
    createParkingLot("Центральная парковка", 25);
    createParkingLot("Северная парковка", 20);
    createParkingLot("Южная парковка", 15);
}

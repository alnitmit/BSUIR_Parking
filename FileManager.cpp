#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "ParkingSpotData.h"

bool FileManager::saveSystemState(const std::vector<VehicleData>& vehicles,
                                  const std::map<int, ParkingLotData>& parkingLots,
                                  int nextLotId) {
    QJsonObject systemState;
    systemState["nextLotId"] = nextLotId;

    QJsonArray vehiclesArray;
    for (const auto& vehicle : vehicles) {
        QJsonObject vehicleObj;
        vehicleObj["type"] = QString::fromStdString(vehicle.getType());
        vehicleObj["model"] = QString::fromStdString(vehicle.getModel());
        vehicleObj["licensePlate"] = QString::fromStdString(vehicle.getLicensePlate());
        vehicleObj["isParked"] = vehicle.isParked();
        
        if (vehicle.getType() == "Truck") {
            vehicleObj["cargoType"] = QString::fromStdString(vehicle.getCargoType());
        }
        
        vehiclesArray.append(vehicleObj);
    }
    systemState["vehicles"] = vehiclesArray;

    QJsonObject lotsObject;
    for (const auto& [lotId, lot] : parkingLots) {
        QJsonObject lotObj;
        lotObj["name"] = QString::fromStdString(lot.getName());
        
        QJsonArray spotsArray;
        for (const auto& spot : lot.getSpots()) {
            QJsonObject spotObj;
            spotObj["number"] = spot.getNumber();
            spotObj["size"] = QString::fromStdString(spot.getSizeString());
            spotObj["occupied"] = spot.isOccupied();
            
            if (spot.isOccupied() && !spot.getVehicleLicensePlate().empty()) {
                spotObj["vehicleLicensePlate"] = QString::fromStdString(spot.getVehicleLicensePlate());
            }
            
            spotsArray.append(spotObj);
        }
        
        lotObj["spots"] = spotsArray;
        lotsObject[QString::number(lotId)] = lotObj;
    }
    systemState["parkingLots"] = lotsObject;

    QJsonDocument doc(systemState);
    QFile file("system_state.json");
    
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for writing: system_state.json" << std::endl;
        return false;
    }
    
    file.write(doc.toJson());
    file.close();
    return true;
}

bool FileManager::loadSystemState(std::vector<VehicleData>& vehicles,
                                  std::map<int, ParkingLotData>& parkingLots,
                                  int& nextLotId) {
    QFile file("system_state.json");
    
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        return false;
    }
    
    QJsonObject systemState = doc.object();
    nextLotId = systemState["nextLotId"].toInt();
    
    vehicles.clear();
    QJsonArray vehiclesArray = systemState["vehicles"].toArray();
    for (const auto& value : vehiclesArray) {
        QJsonObject vehicleObj = value.toObject();
        VehicleData vehicle;
        vehicle.setType(vehicleObj["type"].toString().toStdString());
        vehicle.setModel(vehicleObj["model"].toString().toStdString());
        vehicle.setLicensePlate(vehicleObj["licensePlate"].toString().toStdString());
        vehicle.setParked(vehicleObj["isParked"].toBool());
        
        if (vehicle.getType() == "Truck") {
            vehicle.setCargoType(vehicleObj["cargoType"].toString().toStdString());
        }
        
        vehicles.push_back(vehicle);
    }
    
    parkingLots.clear();
    QJsonObject lotsObject = systemState["parkingLots"].toObject();
    for (auto it = lotsObject.begin(); it != lotsObject.end(); ++it) {
        int lotId = it.key().toInt();
        QJsonObject lotObj = it.value().toObject();
        
        ParkingLotData lot(lotId, lotObj["name"].toString().toStdString());
        
        QJsonArray spotsArray = lotObj["spots"].toArray();
        for (const auto& spotValue : spotsArray) {
            QJsonObject spotObj = spotValue.toObject();
            ParkingSpotData spot(spotObj["number"].toInt(), 
                                ParkingSpotData::parseSize(spotObj["size"].toString().toStdString()));
            spot.setOccupied(spotObj["occupied"].toBool());
            
            if (spot.isOccupied() && spotObj.contains("vehicleLicensePlate")) {
                spot.setVehicleLicensePlate(spotObj["vehicleLicensePlate"].toString().toStdString());
            }
            
            lot.addSpot(spot);
        }
        
        parkingLots[lotId] = lot;
    }
    
    return true;
}

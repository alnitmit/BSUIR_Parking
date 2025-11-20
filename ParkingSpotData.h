#ifndef PARKINGSPOTDATA_H
#define PARKINGSPOTDATA_H

#include <string>
#include <optional>

class ParkingSpotData {
public:
    enum class Size { COMPACT, STANDARD, LARGE };

    ParkingSpotData();
    ParkingSpotData(int number, Size size);
    
    int getNumber() const;
    void setNumber(int number);
    
    Size getSize() const;
    void setSize(Size size);
    
    std::string getSizeString() const;
    
    bool isOccupied() const;
    void setOccupied(bool occupied);
    
    std::string getVehicleLicensePlate() const;
    void setVehicleLicensePlate(const std::string& licensePlate);
    
    std::optional<std::string> getParkingTime() const;
    void setParkingTime(const std::optional<std::string>& time);
    void clearParkingTime();

    static Size parseSize(const std::string& str);

private:
    int number_;
    Size size_;
    bool occupied_;
    std::string vehicleLicensePlate_;
    std::optional<std::string> parkingTime_;
};

#endif

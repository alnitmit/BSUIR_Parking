#ifndef PARKINGSPOTDATA_H
#define PARKINGSPOTDATA_H

#include <string>
#include <optional>
#include <string_view>

class ParkingSpotData {
public:
    enum class Size { Compact, Standard, Large };

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
    void setVehicleLicensePlate(std::string_view licensePlate);

    void occupy(std::string_view licensePlate);
    void release();

    std::optional<std::string> getParkingTime() const;
    void setParkingTime(const std::optional<std::string>& time);
    void clearParkingTime();

    static Size parseSize(std::string_view str);
    static std::string sizeToString(Size size);

private:
    int number_;
    Size size_;
    bool occupied_ = false;
    std::string vehicleLicensePlate_;
    std::optional<std::string> parkingTime_;
};

#endif

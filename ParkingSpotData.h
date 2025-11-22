#ifndef PARKINGSPOTDATA_H
#define PARKINGSPOTDATA_H

#include <string>
#include <optional>

class ParkingSpotData {
public:
    enum class Size { Compact, Standard, Large };  // Исправлено: добавлены значения

    ParkingSpotData();
    ParkingSpotData(int number, Size size);

    int getNumber() const;
    void setNumber(int number);

    Size getSize() const;
    void setSize(Size size);

    std::string getSizeString() const;

    bool isOccupied() const;
    void setOccupied(bool occupied);

    std::string getVehicleLicensePlate() const;  // Исправлено: убрана ссылка
    void setVehicleLicensePlate(const std::string& licensePlate);

    // Добавлены отсутствующие методы
    void occupy(const std::string& licensePlate);
    void release();

    std::optional<std::string> getParkingTime() const;
    void setParkingTime(const std::optional<std::string>& time);
    void clearParkingTime();

    static Size parseSize(const std::string& str);
    static std::string sizeToString(Size size);  // Добавлен отсутствующий метод

private:
    int number_;
    Size size_;
    bool occupied_;
    std::string vehicleLicensePlate_;
    std::optional<std::string> parkingTime_;
};

#endif

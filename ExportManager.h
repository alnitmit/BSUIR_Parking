#ifndef EXPORTMANAGER_H
#define EXPORTMANAGER_H

#include <QString>
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "ParkingSpot.h"

class ExportManager {
public:
    static bool exportToJson(const std::vector<std::shared_ptr<Vehicle>>& vehicles,
                             const std::vector<std::shared_ptr<ParkingSpot>>& spots,
                             const QString& filename);

    static bool exportToCsv(const std::vector<std::shared_ptr<Vehicle>>& vehicles,
                            const std::vector<std::shared_ptr<ParkingSpot>>& spots,
                            const QString& filename);
};

#endif // EXPORTMANAGER_H

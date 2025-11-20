#include "DataRepository.h"

DataRepository& DataRepository::getInstance() {
    static DataRepository instance;
    return instance;
}

void DataRepository::clear() {
    vehicles_.clear();
    lots_.clear();
    nextLotId_ = 1;
}


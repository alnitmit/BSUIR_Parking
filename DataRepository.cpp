#include "DataRepository.h"

// Определяем статическую переменную в cpp файле
DataRepository& DataRepository::getInstance() {
    static DataRepository instance;
    return instance;
}

void DataRepository::clear() {
    vehicles_.clear();
    lots_.clear();
    nextLotId_ = 1;
}

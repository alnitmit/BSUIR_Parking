#include "DataRepository.h"

void DataRepository::clear() {
    vehicles_.clear();
    lots_.clear();
    nextLotId_ = 1;
}


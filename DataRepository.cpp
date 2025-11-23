#include "DataRepository.h"

DataRepository& DataRepository::getInstance() {
    if (!instance_) {
        instance_ = new DataRepository();
    }
    return *instance_;
}

void DataRepository::clear() {
    vehicles_.clear();
    lots_.clear();
    nextLotId_ = 1;
}

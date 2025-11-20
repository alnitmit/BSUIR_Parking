#include "InputValidator.h"

QString InputValidator::lastError_;

bool InputValidator::isValidLicensePlate(const QString& plate) {
    if (QRegularExpression regex(R"(^[A-Z0-9]{1,10}$)"); !regex.match(plate).hasMatch()) {
        lastError_ = "License plate must contain only uppercase letters and numbers (1-10 characters)";
        return false;
    }
    return true;
}

bool InputValidator::isValidTimeFormat(const QString& time) {
    if (QRegularExpression regex(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)"); !regex.match(time).hasMatch()) {
        lastError_ = "Time must be in format: YYYY-MM-DD HH:MM:SS";
        return false;
    }
    return true;
}

bool InputValidator::isValidSpotNumber(int number, int min, int max) {
    if (number < min || number > max) {
        lastError_ = QString("Spot number must be between %1 and %2").arg(min).arg(max);
        return false;
    }
    return true;
}

QString InputValidator::formatLicensePlate(const QString& plate) {
    return plate.toUpper().simplified();
}

QString InputValidator::getErrorString() {
    return lastError_;
}

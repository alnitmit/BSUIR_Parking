#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
#include <QString>
#include <QRegularExpression>

class InputValidator {
public:
    static bool isValidLicensePlate(const QString& plate);
    static bool isValidTimeFormat(const QString& time);
    static bool isValidSpotNumber(int number, int min = 1, int max = 1000);
    static QString formatLicensePlate(const QString& plate);

    static QString getErrorString();

private:
    static QString lastError_;
};

#endif // INPUTVALIDATOR_H

#include "core/model/ElectricityMeter.h"
#include <sstream>
#include <iomanip>
#include <string>

ElectricityMeter::ElectricityMeter(const Date& date, float value, float voltage)
    : AbstractMeter(date, value), voltage(voltage) {

        if (voltage <= 0.0f) {
            throw std::invalid_argument("Напряжение должно быть положительным.");
        }
        
    }

float ElectricityMeter::getVoltage() const {
    return voltage;
}

std::string ElectricityMeter::getType() const {
    return "Electricity";
}

std::string ElectricityMeter::toString() const {
    std::ostringstream oss;
    oss << "Electricity"
        << " " << getDate().toString()
        << " " << std::fixed << std::setprecision(2) << getValue()
        << " " << voltage;
    return oss.str();
}

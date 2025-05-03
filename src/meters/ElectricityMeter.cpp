#include "meters/ElectricityMeter.h"
#include <sstream>
#include <iomanip>

ElectricityMeter::ElectricityMeter(const Date& date, float value, float voltage)
    : AbstractMeter(date, value), voltage(voltage) {

        if (voltage <= 0.0f) {
            throw std::invalid_argument("Напряжение должно быть положительным.");
        }
        
    }

float ElectricityMeter::getVoltage() const {
    return voltage;
}

std::string ElectricityMeter::toString() const {
    std::ostringstream oss;
    oss << "[Счётчик Электричества] "
        << "Дата: " << getDate().toString()
        << ", Значение: " << std::fixed << std::setprecision(2) << getValue()
        << ", Напряжение: " << voltage << " В";
    return oss.str();
}

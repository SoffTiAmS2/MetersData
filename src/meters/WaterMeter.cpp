#include "meters/WaterMeter.h"
#include <sstream>
#include <iomanip>

WaterMeter::WaterMeter(const Date& date, float value, bool isHot)
    : AbstractMeter(date, value), isHot(isHot) {}

bool WaterMeter::isHotWater() const {
    return isHot;
}

std::string WaterMeter::toString() const {
    std::ostringstream oss;
    oss << "[Счётчик Воды] "
        << "Дата: " << getDate().toString()
        << ", Значение: " << std::fixed << std::setprecision(2) << getValue()
        << ", Тип: " << (isHot ? "горячая" : "холодная");
    return oss.str();
}

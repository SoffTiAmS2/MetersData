#include "core/model/Meters.h"
#include "core/model/Date.h"
#include <sstream>
#include <iomanip>

WaterMeter::WaterMeter(const Date& date, float value, bool isHot)
    : AbstractMeter(date, value), isHot(isHot) {}

bool WaterMeter::isHotWater() const {
    return isHot;
}

std::string WaterMeter::getType() const {
    return "Water";
}

std::string WaterMeter::toString() const {
    std::ostringstream oss;
    oss << "Water"
        << " " << getDate().toString()
        << " " << std::fixed << std::setprecision(2) << getValue()
        << " " << (isHot ? "Hot" : "Cold");
    return oss.str();
}

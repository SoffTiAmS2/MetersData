#include "core/model/Meters.h"
#include "core/model/Date.h"
#include <sstream>
#include <iomanip>

WaterMeter::WaterMeter(const Date& date, float value, bool isHot)
    : AbstractMeter(date, value), isHot(isHot) {}

bool WaterMeter::isHotWater() const {
    return isHot;
}

std::string WaterMeter::toString() const {
    std::ostringstream oss;
    oss << "water "
        << getDate().toString()
        << " " << std::fixed << std::setprecision(2) << getValue()
        << " " << (isHot ? "горячая" : "холодная");
    return oss.str();
}

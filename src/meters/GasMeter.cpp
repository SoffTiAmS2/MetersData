#include "meters/GasMeter.h"
#include <sstream>
#include <iomanip>

GasMeter::GasMeter(const Date& date, float value, const std::string& serialNumber)
    : AbstractMeter(date, value), serialNumber(serialNumber) {

        if (serialNumber.empty()) {
            throw std::invalid_argument("Серийный номер не может быть пустым.");
        }
    }

const std::string& GasMeter::getSerialNumber() const {
    return serialNumber;
}

std::string GasMeter::toString() const {
    std::ostringstream oss;
    oss << "[Газовый счетчик] "
        << "Дата: " << getDate().toString()
        << ", Значение: " << std::fixed << std::setprecision(2) << getValue()
        << ", Серийный номер: " << serialNumber << " В";
    return oss.str();
}

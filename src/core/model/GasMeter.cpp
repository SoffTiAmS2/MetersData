#include "core/model/GasMeter.h"
#include <sstream>
#include <iomanip>



GasMeter::GasMeter(
    const Date& date, 
    float value, 
    const std::string& serialNumber
) : AbstractMeter(date, value), serialNumber(serialNumber) {

    if (serialNumber.empty()) {
        throw std::invalid_argument("Серийный номер не может быть пустым.");
    }
}

const std::string& GasMeter::getSerialNumber() const {
    return serialNumber;
}



std::string GasMeter::getType() const {
    return "Gas";
}

std::string GasMeter::toString() const {
    std::ostringstream oss;
    oss << "Gas"
        << " " << getDate().toString()
        << " " << std::fixed << std::setprecision(2) << getValue()
        << " " << serialNumber;
    
    return oss.str();
}

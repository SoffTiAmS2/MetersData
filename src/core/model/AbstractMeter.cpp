#include "core/model/AbstractMeter.h"
#include "utils/Utils.h"


AbstractMeter::AbstractMeter(const Date& date, float value)
    : date(date), value(value) {
        if (!Utils::isValidDateValues(date.getYear(), date.getMonth(), date.getDay())) {
            throw std::invalid_argument("Некорректная дата.");
        }

        if (value < 0.0f) {
            throw std::invalid_argument("Значение не может быть отрицательным.");
        }
    }

const Date& AbstractMeter::getDate() const { 
    return date; 
}

float AbstractMeter::getValue() const { 
    return value; 
}
#include "Data/Meter.h"

Meter::Meter(std::string type, Date date, float value)
    : type(type), date(date), value(value) {}


const std::string& Meter::getType() const { 
    return type; 
}

const Date& Meter::getDate() const { 
    return date; 
}

const float Meter::getValue() const { 
    return value; 
}

std::string Meter::toString() const {
    return type + ' ' + date.toString() + ' ' + std::to_string(value);
}
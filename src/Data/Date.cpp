#include "Data/Date.h"


Date::Date(int year, int month, int day)
    : year(year), month(month), day(day) {}


const int Date::getYear() const{
    return year;
}

const int Date::getMonth() const {
    return month;
}

const int Date::getDay() const {
    return day;
}


const std::string Date::toString() const {
    return std::to_string(year) + ' ' + std::to_string(month) + ' ' + std::to_string(day);
}
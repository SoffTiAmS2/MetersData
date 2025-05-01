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
    std::string dateStr;
    dateStr += std::to_string(year) + '.';
    dateStr += month > 9 ? std::to_string(month)+ '.' : '0' + std::to_string(month)+ '.';
    dateStr += day > 9 ? std::to_string(day) : '0' + std::to_string(day);
    return dateStr;
}
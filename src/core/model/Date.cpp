#include "core/model/Date.h"
#include "utils/Validator.h"
#include <iomanip>
#include <sstream>

Date::Date(int year, int month, int day)
    : year(year), month(month), day(day) {

        if (!Validator::isValidDateValues(year, month, day)) {
            throw std::invalid_argument("неправильный формат даты");
        }

    }


int Date::getYear() const{
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}


std::string Date::toString() const {
    std::ostringstream oss;
    oss << year << '.'
        << std::setw(2) << std::setfill('0') << month << '.'
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}
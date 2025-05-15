#include "utils/Utils.h"
#include <unicode/unistr.h>
#include <unicode/ustream.h>


bool Utils::isValidDateFormat(const std::string& dateStr) {
    return std::regex_match(dateStr, dateRegex());
}

bool Utils::isValidDateValues(int year, int month, int day) {
    // проверка на правильность чисел годов и дней не может быть меньше 1 и месецев тоже 
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;

    // по умолчанию дней 31
    int daysInMonth = 31;
    
    // условие когда дней может быть 30
    if (month == 4 || month == 6 || month == 9 || month == 11) daysInMonth = 30;

    // условие когда дней может быть 28 или 29 зависит от высокосный год или нет
    else if (month == 2){
        daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    }

    // если количество дней больше чем надо
    return day <= daysInMonth;
}


bool Utils::isValidValue(const std::string& valueStr) {
    return std::regex_match(valueStr, valueRegex());
}

std::string Utils::normalizationString(const std::string& input){

    icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(input);
    ustr.toLower();
    
    std::string result;
    ustr.toUTF8String(result);
    
    return result;
}


const std::regex& Utils::dateRegex() {
    static const std::regex instance(
        R"(^(\d{4})\.(0?[1-9]|1[0-2])\.(0?[1-9]|[12][0-9]|3[01])$)"
    );
    return instance;
}

const std::regex& Utils::valueRegex() {
    static const std::regex instance(
        R"(^[+-]?\d+(?:[.,]\d+)?$)"
    );
    return instance;
}
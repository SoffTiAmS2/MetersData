#include "utils/Validator.h"

bool Validator::isValidType(const std::string& type) {
    return !type.empty(); // Тип не должен быть пустым
}

bool Validator::isValidDateFormat(const std::string& dateStr) {

    bool ok = true;
    int numSeparators = 0;
    for (int i = 0; i < dateStr.size()-1; i++) {
        if(dateStr[i] == '.'){
            numSeparators++;
            continue;
        }

        if(!isdigit(dateStr[i])){
            ok = false;
            break;
        }

    }
    if(numSeparators != 2) ok = false;
    return ok;
}

bool Validator::isValidDateValues(int year, int month, int day) {
    if (year < 0 || month < 1 || month > 12 || day < 1) return false;

    int daysInMonth = 31;
    
    if (month == 4 || month == 6 || month == 9 || month == 11) daysInMonth = 30;
    else if (month == 2) daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;

    return day <= daysInMonth;
}

bool Validator::isValidValue(const std::string& valueStr) {
    if (valueStr.empty()) return false;

    bool hasDecimalPoint = false; // Флаг для десятичной точки
    bool hasDigits = false;       // Флаг для цифр

    for (char ch: valueStr) {
        if (isdigit(ch)) hasDigits = true;
        else if (ch == '.' || ch == ',') {
            if (hasDecimalPoint) return false; // В числе может быть только одна десятичная точка
            hasDecimalPoint = true;
        } else return false;
    }

    return hasDigits;
}
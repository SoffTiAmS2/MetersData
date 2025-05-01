#include "utils/Validator.h"

bool Validator::isValidType(const std::string& type) {
    return !type.empty(); // Тип не должен быть пустым
}

bool Validator::isValidDateFormat(const std::string& dateStr) {

    bool ok = true; // валидность данных
    int numSeparators = 0; // количество разделяемых точек

    for (int i = 0; i < dateStr.size()-1; i++) {
        //если встретили разделитель то увеличиваем инкрементируем количество разделителей
        if(dateStr[i] == '.'){
            numSeparators++;
            continue;
        }

        // у нас могут быть в дате только числа и никакие другие символы
        if(!isdigit(dateStr[i])){
            ok = false;
            break;
        }
    }
    // если количество разделителей больше чем 2 то у нас некоректные данные
    if(numSeparators != 2) ok = false;

    return ok;
}

bool Validator::isValidDateValues(int year, int month, int day) {
    // проверка на правильность чисел годов и дней не может быть меньше 1 и месецев тоже 
    if (year < 0 || month < 1 || month > 12 || day < 1) return false;

    // по умолчанию дней 31
    int daysInMonth = 31;
    
    // условие когда дней может быть 30
    if (month == 4 || month == 6 || month == 9 || month == 11) daysInMonth = 30;

    // условие когда дней может быть 28 или 29 зависит от высокосный год или нет
    else if (month == 2) daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;

    // если количество дней больше чем надо
    return day <= daysInMonth;
}

bool Validator::isValidValue(const std::string& valueStr) {
    if (valueStr.empty()) return false;

    bool hasDecimalPoint = false; // Флаг для десятичной точки
    bool hasDigits = false;       // Флаг для цифр

    //проверяем коректность значения
    for (char ch: valueStr) {
        if (isdigit(ch)) hasDigits = true; //у нас должны быть числа
        else if (ch == '.' || ch == ',') {
            if (hasDecimalPoint) return false; // В числе может быть только одна десятичная точка
            hasDecimalPoint = true;// поднимаем флаг десятичной точки
        } else return false; // у нас не может быть других символов кроме разделительной точки и самих чисел
    }

    return hasDigits;
}
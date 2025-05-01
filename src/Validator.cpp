#include "Validator.h"

bool Validator::isValidType(const std::string& type) {
    return !type.empty(); // Тип не должен быть пустым
}

bool Validator::isValidDateFormat(const std::string& dateStr) {
    // Проверяем длину строки
    if (dateStr.length() != 10) {
        return false; // Формат гггг.мм.дд всегда имеет длину 10 символов
    }

    // Проверяем разделители (точки)
    if (dateStr[4] != '.' || dateStr[7] != '.') {
        return false;
    }

    // Проверяем, что все остальные символы — цифры
    for (size_t i = 0; i < dateStr.length(); ++i) {
        if (i == 4 || i == 7) continue; // Пропускаем точки
        if (!isdigit(dateStr[i])) {
            return false;
        }
    }

    return true;
}

bool Validator::isValidDateValues(int year, int month, int day) {
    if (year < 0 || month < 1 || month > 12 || day < 1) return false;

    int daysInMonth = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else if (month == 2) {
        daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    }

    return day <= daysInMonth;
}

bool Validator::isValidValue(const std::string& valueStr) {
    if (valueStr.empty()) {
        return false; // Пустая строка не является числом
    }

    bool hasDecimalPoint = false; // Флаг для десятичной точки
    bool hasDigits = false;       // Флаг для цифр

    for (size_t i = 0; i < valueStr.length(); ++i) {
        char ch = valueStr[i];

        if (isdigit(ch)) {
            hasDigits = true; // Нашли хотя бы одну цифру
        } else if (ch == '.') {
            if (hasDecimalPoint) {
                return false; // В числе может быть только одна десятичная точка
            }
            hasDecimalPoint = true;
        } else {
            return false; // Недопустимый символ
        }
    }

    return hasDigits; // Число должно содержать хотя бы одну цифру
}
#pragma once
#include <string>


class Validator {
public:
    // Проверка типа ресурса (не пустая строка)
    static bool isValidType(const std::string& type);

    // Проверка формата даты (гггг.мм.дд)
    static bool isValidDateFormat(const std::string& dateStr);

    // Проверка корректности значений даты
    static bool isValidDateValues(int year, int month, int day);

    // Проверка числового значения
    static bool isValidValue(const std::string& valueStr);
};
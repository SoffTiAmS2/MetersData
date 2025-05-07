#pragma once
#include <string>
#include <regex>

class Utils {
public:
    // Проверка формата даты (гггг.мм.дд)
    static bool isValidDateFormat(const std::string& dateStr);

    // Проверка корректности значений даты
    static bool isValidDateValues(int year, int month, int day);

    // Проверка числового значения
    static bool isValidValue(const std::string& valueStr);

    static std::string normalizationString(const std::string& input);

    static const std::regex& dateRegex();
    static const std::regex& valueRegex();
};
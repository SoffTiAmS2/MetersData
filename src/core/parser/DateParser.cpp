#include "core/parser/DateParser.h"
#include "utils/Utils.h"
#include <stdexcept>

Date DateParser::parse(const std::string& input) const {
    // Проверяем формат даты
    if (!Utils::isValidDateFormat(input)) {
        throw std::invalid_argument("Неправильный формат даты: " + input);
    }

    std::smatch matches;
    std::regex_match(input, matches, Utils::dateRegex());

    // Парсим значения года, месяца и дня
    int year = std::stoi(matches[1].str());
    int month = std::stoi(matches[2].str());
    int day = std::stoi(matches[3].str());

    // Проверяем корректность значений даты
    if (!Utils::isValidDateValues(year, month, day)) {
        throw std::invalid_argument("Неправильный формат даты: " + input);
    }

    // Возвращаем объект Date
    return Date(year, month, day);
}

#include "parsers/StringDateParser.h"
#include "utils/Validator.h"
#include <stdexcept>

Date StringDateParser::parse(const std::string& input) const {
    // Проверяем формат даты
    if (!Validator::isValidDateFormat(input)) {
        throw std::invalid_argument("Неправильный формат даты: " + input);
    }

    // Находим позиции точек
    size_t pos1 = input.find('.');
    size_t pos2 = input.find('.', pos1 + 1);

    // Парсим значения года, месяца и дня
    int year = std::stoi(input.substr(0, pos1));
    int month = std::stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
    int day = std::stoi(input.substr(pos2 + 1));

    // Проверяем корректность значений даты
    if (!Validator::isValidDateValues(year, month, day)) {
        throw std::invalid_argument("Неправильный формат даты: " + input);
    }

    // Возвращаем объект Date
    return Date(year, month, day);
}

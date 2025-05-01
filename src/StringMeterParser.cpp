#include "StringMeterParser.h"
#include "Validator.h"

bool StringMeterParser::parse(const std::string& input, Meter& meter) {
    // Находим позицию последнего пробела
    size_t lastSpace = input.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        return false; // Недостаточно данных
    }

    // Выделяем последний токен (значение)
    std::string valueStr = input.substr(lastSpace + 1);

    // Находим позицию предпоследнего пробела
    size_t secondLastSpace = input.find_last_of(' ', lastSpace - 1);
    if (secondLastSpace == std::string::npos) {
        return false; // Недостаточно данных
    }

    // Выделяем предпоследний токен (дата)
    std::string dateStr = input.substr(secondLastSpace + 1, lastSpace - secondLastSpace - 1);

    // Остальная часть строки — это тип ресурса
    std::string type = input.substr(0, secondLastSpace);

    // Проверяем валидность типа
    if (!Validator::isValidType(type)) {
        return false;
    }

    // Проверяем формат даты
    if (!Validator::isValidDateFormat(dateStr)) {
        return false;
    }

    // Парсим значения даты
    size_t pos1 = dateStr.find('.');
    size_t pos2 = dateStr.find('.', pos1 + 1);
    int year = std::stoi(dateStr.substr(0, pos1));
    int month = std::stoi(dateStr.substr(pos1 + 1, pos2 - pos1 - 1));
    int day = std::stoi(dateStr.substr(pos2 + 1));

    // Проверяем корректность значений даты
    if (!Validator::isValidDateValues(year, month, day)) {
        return false;
    }

    // Проверяем валидность значения
    if (!Validator::isValidValue(valueStr)) {
        return false;
    }

    float value = std::stof(valueStr);

    // Заполняем объект Meter
    meter = Meter(type, Date(year, month, day), value);
    return true;
}
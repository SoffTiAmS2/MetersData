#include "parsUtils/ValueParser.h"
#include "utils/Validator.h"

float ValueParser::parse(const std::string& input) const {
    //проверяем правильность значения
    if(!Validator::isValidValue(input)){
        throw std::invalid_argument("Неправильный формат значения " + input);
    }

    std::string floatStr = input;

    // Заменяем запятую на точку
    std::replace(floatStr.begin(), floatStr.end(), ',', '.');

    // Возращаем наше значение 
    return std::stof(floatStr);
}
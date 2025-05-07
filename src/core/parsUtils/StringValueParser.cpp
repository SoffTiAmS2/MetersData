#include "core/parsUtils/ValueParser.h"
#include "utils/Utils.h"

float ValueParser::parse(const std::string& input) const {
    //проверяем правильность значения
    if(!Utils::isValidValue(input)){
        throw std::invalid_argument("Неправильный формат значения " + input);
    }

    std::string floatStr = input;

    // Заменяем запятую на точку
    std::replace(floatStr.begin(), floatStr.end(), ',', '.');

    float value = std::stof(floatStr);
    // Возращаем наше значение 
    return value;
}
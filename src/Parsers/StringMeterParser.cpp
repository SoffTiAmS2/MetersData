#include "parsers/StringMeterParser.h"
#include "meters/AbstractMeter.h"
#include <cctype>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


std::string StringMeterParser::normalizeType(const std::string& type) const {
    std::string normalized;

    for (char ch : type) {
        normalized += std::tolower(ch);
    }
    return normalized;
}


std::unique_ptr<AbstractMeter> StringMeterParser::parse(const std::string& input) {
    try {
        
        std::vector<std::string> tokens = splitter.split(input);
        if (tokens.size() < 4) {
            throw std::invalid_argument("Mало данных " + input);
        }
        //забираем 4 токена с типом датой и значением параметр
        std::string typeStr = normalizeType(tokens[0]); // 1-я группа - тип
        std::string dateStr  = tokens[1]; // 2-я группа - дата
        std::string valueStr = tokens[2]; // 3-я группа - значение
        std::string param = normalizeType(tokens[3]); // 4-я группа - параметр

        // парсим дату значение
        Date date = dateParser.parse(dateStr);
        float value = valueParser.parse(valueStr);
        
        return factory.createMeter(typeStr, date, value, param);
    } 
    
    catch (const std::exception& e) {
        // если произошло исключение в прощессе парса
        throw; // Пробрасываем исключение дальше
    }
}
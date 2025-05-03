#include "Parsers/StringMeterParser.h"
#include "meters/AbstractMeter.h"
#include <memory>
#include <stdexcept>


std::unique_ptr<AbstractMeter> StringMeterParser::parse(const std::string& input) {
    try {
        // разбиваем входные данные на токены 
        std::vector<std::string> tokens = splitter.split(input);

        // если токенов меньше чем 3 то у нас недостаточно данных
        if (tokens.size() < 4) {
            throw std::invalid_argument("Недостаточно данных в: " + input);
        }

        //забираем 3 последних токена с типом датой и значением
        std::string typeStr = tokens[tokens.size() - 4]; 
        std::string dateStr = tokens[tokens.size() - 3];
        std::string valueStr = tokens[tokens.size() - 2];
        std::string param = tokens[tokens.size() - 1];

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
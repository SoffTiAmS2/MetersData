#include "core/parser/StringMeterParser.h"
#include "core/model/AbstractMeter.h"
#include <locale>
#include <memory>
#include <stdexcept>
#include <QString>
#include <vector>
#include "utils/Logger.h"
#include "utils/Utils.h"


StringMeterParser::StringMeterParser(std::unique_ptr<ISpliter> splitter) 
    : splitter(std::move(splitter)) {}

std::unique_ptr<AbstractMeter> StringMeterParser::parse(const std::string& input) const {
    std::vector<std::string>  tokens = splitter->split(input);
    if (tokens.size() < 4) {
        throw std::invalid_argument("Недостаточно данных в строке: " + input);
    }

    std::string typeStr = Utils::normalizationString(tokens[0]);
    std::string dateStr = tokens[1];
    std::string valueStr = tokens[2];
    std::string paramStr = tokens[3];

    try {
        Date date = dateParser.parse(dateStr);
        float value = valueParser.parse(valueStr);
        
        return factory.createMeter(typeStr, date, value, paramStr);
    } 
    catch (const std::exception& e) {
        std::string message = std::string("Ошибка парсинга: ") + e.what() + " в " + input;
        throw std::invalid_argument(message);
        return nullptr;
    }
}
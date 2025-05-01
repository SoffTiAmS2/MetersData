#include "Parsers/StringMeterParser.h"
#include "utils/Validator.h"
#include <stdexcept>

std::vector<std::string> StringMeterParser::splitString(const std::string& input){
    std::vector<std::string> Tokens;
    bool itsStr = false;

    std::string token;

    for(char ch: input){
        if(ch == '"' or ch == '\'') itsStr = !itsStr;

        if(ch == ' ' and !itsStr){
            if(!token.empty()){ 
                Tokens.push_back(token);
                token.clear();
            }
            continue;
        }  
        token += ch;
    }

    if (!token.empty()) {
        Tokens.push_back(token);
    }

    return Tokens;
}

std::string typeParse(const std::string& token){
    if (!Validator::isValidType(token)) {
        throw std::invalid_argument("Empty Type");
    }
    std::string TypeStr;
    int start = token[0] == '"' ? 1 : 0;
    int end = token[token.size()-1] == '"' ? token.size() : token.size()-1;

    if(start == end){
        throw std::invalid_argument("Empty Type");
    }

    return token.substr(start, end - start);
}

Date StringMeterParser::dateParse(const std::string& token) {
    // Проверяем формат даты
    if (!Validator::isValidDateFormat(token)) {
        throw std::invalid_argument("Invalid date format: " + token);
    }

    // Находим позиции точек
    size_t pos1 = token.find('.');
    size_t pos2 = token.find('.', pos1 + 1);

    // Парсим значения года, месяца и дня
    int year = std::stoi(token.substr(0, pos1));
    int month = std::stoi(token.substr(pos1 + 1, pos2 - pos1 - 1));
    int day = std::stoi(token.substr(pos2 + 1));

    // Проверяем корректность значений даты
    if (!Validator::isValidDateValues(year, month, day)) {
        throw std::invalid_argument("Invalid date values: " + token);
    }

    // Возвращаем объект Date
    return Date(year, month, day);
}

float valueParse(const std::string& token){
    if(!Validator::isValidValue(token)){
        throw std::invalid_argument("Invalid value format: " + token);
    }

    return std::stof(token);

}

Meter StringMeterParser::parse(const std::string& input) {
    try {
        std::vector<std::string> tokens = splitString(input);
        if (tokens.size() < 3) {
            throw std::invalid_argument("Insufficient tokens in input: " + input);
        }

        std::string typeStr = tokens[tokens.size() - 3]; 
        std::string dateStr = tokens[tokens.size() - 2];
        std::string valueStr = tokens[tokens.size() - 1];

        std::string type = typeParse(typeStr);
        Date date = dateParse(dateStr);
        float value = valueParse(valueStr);

        return Meter(type, date, value);
    } 
    
    catch (const std::exception& e) {
        // std::cerr << "Error parsing input: " << e.what() << std::endl;
        throw; // Пробрасываем исключение дальше
    }
}
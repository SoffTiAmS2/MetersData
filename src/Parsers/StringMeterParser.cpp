#include "Parsers/StringMeterParser.h"
#include "utils/Validator.h"
#include <stdexcept>


std::vector<std::string> StringMeterParser::splitString(const std::string& input){
    // инциализируем переменные
    std::vector<std::string> Tokens; // масив токенов
    bool itsStrSpace = false; //это строка с пробeлами?
    std::string token; //текущий токен

    //разбиваем строку на масив токенов
    for(char ch: input){
        //это строка?
        if(ch == '"' or ch == '\'') itsStrSpace = !itsStrSpace;

        //если не строка с пробелами
        if(ch == ' ' and !itsStrSpace){
            //если мы встретили пробел и при этом текущий токен не пустой
            if(!token.empty()){ 
                Tokens.push_back(token);
                token.clear(); //очищаем текущий токен для новых данных
            }
            continue;
        }  
        token += ch; //добавляем символ в наш токен
    }

    // если у нас остался токен
    if (!token.empty()) {
        Tokens.push_back(token);
    }

    return Tokens;
}

std::string StringMeterParser::typeParse(const std::string& token){
    // проверяем валидность типа
    if (!Validator::isValidType(token)) {
        throw std::invalid_argument("Пустое поле \" Тип \" ");
    }

    // убираем ковычки в строке для этого найдем их положение
    int start = token[0] == '"' ? 1 : 0;
    int end = token[token.size()-1] == '"' ? token.size() : token.size()-1;

    // если нет строки в ковычках то у нас пустое поле
    if(start == end-1){
        throw std::invalid_argument("Пустое поле \" Тип \" ");
    }

    // возращаем наш тип
    return token.substr(start, end - start-1);
}

Date StringMeterParser::dateParse(const std::string& token) {
    // Проверяем формат даты
    if (!Validator::isValidDateFormat(token)) {
        throw std::invalid_argument("Неправильный формат даты: " + token);
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
        throw std::invalid_argument("Неправильный формат даты: " + token);
    }

    // Возвращаем объект Date
    return Date(year, month, day);
}

float StringMeterParser::valueParse(const std::string& token){
    //проверяем правильность значения
    if(!Validator::isValidValue(token)){
        throw std::invalid_argument("Неправильный формат значения " + token);
    }

    std::string floatStr = token;

    // Заменяем запятую на точку
    std::replace(floatStr.begin(), floatStr.end(), ',', '.');

    // Возращаем наше значение 
    return std::stof(floatStr);

}

Meter StringMeterParser::parse(const std::string& input) {
    try {
        // разбиваем входные данные на токены 
        std::vector<std::string> tokens = splitString(input);

        // если токенов меньше чем 3 то у нас недостаточно данных
        if (tokens.size() < 3) {
            throw std::invalid_argument("Недостаточно данных в: " + input);
        }

        //забираем 3 последних токена с типом датой и значением
        std::string typeStr = tokens[tokens.size() - 3]; 
        std::string dateStr = tokens[tokens.size() - 2];
        std::string valueStr = tokens[tokens.size() - 1];

        // парсим тип дату значение
        std::string type = typeParse(typeStr);
        Date date = dateParse(dateStr);
        float value = valueParse(valueStr);

        return Meter(type, date, value);
    } 
    
    catch (const std::exception& e) {
        // если произошло исключение в прощессе парса
        throw; // Пробрасываем исключение дальше
    }
}
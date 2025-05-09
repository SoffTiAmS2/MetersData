#include "core/parsUtils/StringSplitter.h"

std::vector<std::string> StringSplitter::split(const std::string& input) const {

    std::vector<std::string> tokens;
    bool itsStrSpace = false; //это строка с пробeлами?
    std::string token; //текущий токен

    //разбиваем строку на масив токенов
    for(const char& ch: input){
        //это строка?
        if(ch == '"' or ch == '\'') {
            itsStrSpace = !itsStrSpace;
            continue;
        }

        if(ch == ' ' and !itsStrSpace){
            //если мы встретили пробел и при этом текущий токен не пустой
            if(!token.empty()) { 
                tokens.push_back(token);
                token.clear(); //очищаем текущий токен для новых данных
            }
            continue;
        }  
        token += ch; //добавляем символ в наш токен
    }

    // если у нас остался токен
    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
} 

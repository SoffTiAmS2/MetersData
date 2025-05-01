#pragma once
#include "interfaces/IMeterParser.h"
#include <vector>

class StringMeterParser : public IMeterParser {
private:
    // Разбивает строку на токены
    std::vector<std::string> splitString(const std::string& input);

    //парс типа
    std::string typeParse(const std::string& token);
    //парс даты
    Date dateParse(const std::string& token);
    //парс значения
    float valueParse(const std::string& token);

public:
    Meter parse(const std::string& input) override;
};
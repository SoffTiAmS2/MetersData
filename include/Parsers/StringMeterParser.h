#pragma once
#include "interfaces/IMeterParser.h"
#include <vector>

class StringMeterParser : public IMeterParser {
private:
    // Разбивает строку на токены
    std::vector<std::string> splitString(const std::string& input);
    std::string typeParse(const std::string& token);
    Date dateParse(const std::string& token);
    float valueParse(const std::string& token);

public:
    Meter parse(const std::string& input) override;
};
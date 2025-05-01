#pragma once
#include "IMeterParser.h"
#include <vector>

class StringMeterParser : public IMeterParser {
private:
    // Разбивает строку на токены
    std::vector<std::string> splitString(const std::string& input);
    std::string typeParse(const std::string& token);
    Date dateparse(const std::string& token);
    float valueParse(const std::string& token);

public:
    bool parse(const std::string& input, Meter& meter) override;
};
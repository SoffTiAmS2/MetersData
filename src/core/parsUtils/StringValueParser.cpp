#include "core/parsUtils/ValueParser.h"
#include "utils/Utils.h"
#include <cmath>

float ValueParser::parse(const std::string& input) const {
    if (!Utils::isValidValue(input)) {
        throw std::invalid_argument("Неверный формат значения: " + input);
    }

    // Реальный парсинг
    std::string s = input;
    size_t i = 0;
    bool negative = false;

    // Знак
    if (s[i] == '-') {
        negative = true;
        ++i;
    } else if (s[i] == '+') {
        ++i;
    }

    float value = 0.0f;

    // Целая часть
    while (i < s.size() && std::isdigit(s[i])) {
        value = value * 10 + (s[i] - '0');
        ++i;
    }

    // Дробная часть
    if (i < s.size() && (s[i] == '.' || s[i] == ',')) {
        ++i;
        float factor = 0.1f;
        while (i < s.size() && std::isdigit(s[i])) {
            value += (s[i] - '0') * factor;
            factor *= 0.1f;
            ++i;
        }
    }
    
    value = std::ceilf(value * 100.0f) / 100.0f;

    return negative ? -value : value;
}

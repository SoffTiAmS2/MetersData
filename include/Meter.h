#pragma once
#include <string>
#include "Date.h"

class Meter {
private:
    std::string type;
    Date date;
    float value;

public:
    // Конструктор
    Meter(std::string type, Date date, float value);

    // Геттеры
    const std::string& getType() const { return type; }
    const Date& getDate() const { return date; }
    float getValue() const { return value; }

    // Метод для строкового представления
    std::string toString() const {
        return type + date.toString() + std::to_string(value);
    }
};
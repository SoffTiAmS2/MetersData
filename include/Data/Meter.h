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
    const std::string& getType() const;
    const Date& getDate() const;
    const float getValue() const;

    // Метод для строкового представления
    std::string toString() const;
};
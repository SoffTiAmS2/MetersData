#pragma once
#include <string>
#include "models/Date.h"


class AbstractMeter {
    protected:
        Date date;
        float value;
    public:
        AbstractMeter(const Date& date, float value);

        virtual ~AbstractMeter() = default;
    
        const Date& getDate() const;
        float getValue() const;
        // Общий метод
        virtual std::string toString() const = 0;
    };
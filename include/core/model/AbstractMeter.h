#pragma once

#include <string>
#include "Date.h"



class AbstractMeter { 
public:
    AbstractMeter(const Date& date, float value);

    const Date& getDate() const;
    float getValue() const;
    
    virtual std::string getType() const = 0;
    virtual std::string toString() const = 0;
    
    virtual ~AbstractMeter() = default;

protected:
    Date date;
    float value;
};
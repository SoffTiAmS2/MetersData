#pragma once

#include "AbstractMeter.h"
#include "Date.h"


class WaterMeter : public AbstractMeter {
public:
    WaterMeter(const Date& date, float value, bool isHot);
    
    bool isHotWater() const;
    
    std::string getType() const override; 
    std::string toString() const override;

private:
    bool isHot;   // Напряжение
};
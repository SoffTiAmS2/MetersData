// include/Data/ElectricityMeter.h
#pragma once
#include "AbstractMeter.h"
#include "core/model/Date.h"

class WaterMeter : public AbstractMeter {
private:
    bool isHot;   // Напряжение

public:
    WaterMeter(const Date& date, float value, bool isHot);

    bool isHotWater() const;

    std::string getType() const override; 
    std::string toString() const override;
};
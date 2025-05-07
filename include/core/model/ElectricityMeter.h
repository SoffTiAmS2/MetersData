// include/Data/ElectricityMeter.h
#pragma once
#include "AbstractMeter.h"


class ElectricityMeter : public AbstractMeter {
private:
    float voltage;   // Напряжение

public:
    ElectricityMeter(const Date& date, float value, float voltage);

    float getVoltage() const;
    std::string getType() const override; 
    std::string toString() const override;
};
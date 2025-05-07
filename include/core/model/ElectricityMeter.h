#pragma once

#include "AbstractMeter.h"




class ElectricityMeter : public AbstractMeter {    
public:
    ElectricityMeter(const Date& date, float value, float voltage);
    
    float getVoltage() const;
    
    std::string getType() const override; 
    std::string toString() const override;

private:
    float voltage;   // Напряжение
};
// include/Data/ElectricityMeter.h
#pragma once
#include "AbstractMeter.h"

class GasMeter : public AbstractMeter {
private:
    std::string serialNumber;   // Напряжение

public:
    GasMeter(const Date& date, float value,
        const std::string& serialNumber);

    const std::string& getSerialNumber() const;

    std::string getType() const override; 
    std::string toString() const override;
};
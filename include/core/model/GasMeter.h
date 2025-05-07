#pragma once

#include "AbstractMeter.h"




class GasMeter : public AbstractMeter {
public:
    GasMeter(const Date& date, float value,
        const std::string& serialNumber);
    

    const std::string& getSerialNumber() const;
    std::string getType() const override; 
    std::string toString() const override;

private:
    std::string serialNumber;
};
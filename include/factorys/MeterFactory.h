#pragma once

#include "meters/AbstractMeter.h"
#include "models/Date.h"
#include <memory>
#include <string>

class MeterFactory {
public:
    std::unique_ptr<AbstractMeter> createMeter(const std::string& type,
        const Date& date, float value, const std::string& param);
};


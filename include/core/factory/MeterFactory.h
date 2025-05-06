#pragma once

#include "core/model/AbstractMeter.h"
#include "core/model/Date.h"
#include <memory>
#include <string>

class MeterFactory {
public:
    std::unique_ptr<AbstractMeter> createMeter(const std::string& type,
        const Date& date, float value, const std::string& param);
};


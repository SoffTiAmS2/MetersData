#pragma once
#include "Data/Meter.h"

class IMeterParser {
public:
    virtual ~IMeterParser() = default;
    virtual Meter parse(const std::string& input) = 0;
};
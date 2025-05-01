#pragma once
#include "Meter.h"

class IMeterParser {
public:
    virtual ~IMeterParser() = default;
    virtual bool parse(const std::string& input, Meter& meter) = 0;
};
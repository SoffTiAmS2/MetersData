#pragma once

#include "core/model/AbstractMeter.h"




class IMeterParser {    
public:
    virtual ~IMeterParser() = default;
    virtual std::unique_ptr<AbstractMeter> parse(const std::string& input) const = 0;
};
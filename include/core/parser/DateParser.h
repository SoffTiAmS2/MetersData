#pragma once

#include "core/model/Date.h"
#include <string>



class DateParser {
public:
    Date parse(const std::string& input) const;
};
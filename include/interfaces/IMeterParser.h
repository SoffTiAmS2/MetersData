#pragma once
#include "Data/Meter.h"

// Интерфейс парсера данных счетчика
class IMeterParser {
public:

    virtual ~IMeterParser() = default;
    virtual Meter parse(const std::string& input) = 0;
};
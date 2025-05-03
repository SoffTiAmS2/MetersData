#pragma once
#include "meters/AbstractMeter.h"
#include <memory>

// Интерфейс парсера данных счетчика
class IMeterParser {
public:
    virtual ~IMeterParser() = default;

    virtual std::unique_ptr<AbstractMeter> parse(const std::string& input) = 0;
};
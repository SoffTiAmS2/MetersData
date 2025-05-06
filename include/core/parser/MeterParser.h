#pragma once
#include "DateParser.h"
#include "core/factory/MeterFactory.h"
#include "core/model/AbstractMeter.h"
#include "core/parsUtils/ISpliter.h"
#include "core/parsUtils/ValueParser.h"
#include <string>
#include <memory>

class MeterParser {
public:
    explicit MeterParser(std::unique_ptr<ISpliter> splitter);
    std::unique_ptr<AbstractMeter> parse(const std::string& input);

private:

    MeterFactory factory;
    std::unique_ptr<ISpliter> splitter;
    DateParser dateParser;
    ValueParser valueParser;
};
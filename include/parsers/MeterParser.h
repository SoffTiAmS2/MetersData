#pragma once

#include "factorys/MeterFactory.h"
#include "parsUtils/ISpliter.h"
#include "parsUtils/ValueParser.h"
#include "DateParser.h"
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
#pragma once

#include "factorys/MeterFactory.h"
#include "interfaces/IMeterParser.h"
#include "parsUtils/StringSplitter.h"
#include "parsUtils/StringValueParser.h"
#include "StringDateParser.h"
#include <string>
#include <memory>


class StringMeterParser : public IMeterParser {
public:
    std::unique_ptr<AbstractMeter> parse(const std::string& input) override;

private:
    MeterFactory factory;
    StringSplitter splitter;
    StringDateParser dateParser;
    StringValueParser valueParser;
};
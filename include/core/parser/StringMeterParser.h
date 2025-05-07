#pragma once

#include "DateParser.h"
#include "core/factory/MeterFactory.h"
#include "core/model/AbstractMeter.h"
#include "core/parsUtils/ISpliter.h"
#include "core/parsUtils/ValueParser.h"
#include "IMeterParser.h"
#include <string>
#include <memory>

class StringMeterParser : public IMeterParser{
public:
    explicit StringMeterParser(std::unique_ptr<ISpliter> splitter);
    std::unique_ptr<AbstractMeter> parse(const std::string& input) const override;

private:
    MeterFactory factory;
    std::unique_ptr<ISpliter> splitter;
    DateParser dateParser;
    ValueParser valueParser;
};
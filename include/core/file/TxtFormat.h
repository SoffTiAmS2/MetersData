// include/file/TxtFormat.h
#pragma once
#include "core/file/IFileFormat.h"
#include "core/parser/MeterParser.h"

class TxtFormat : public IFileFormat {
public:
    TxtFormat();
    MeterList parse(QTextStream& input) override;
    QString serialize(const MeterList& data) override;
private:
    QString formatMeter(const AbstractMeter* meter);
    MeterParser parser;
};
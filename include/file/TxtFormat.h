// include/file/TxtFormat.h
#pragma once
#include "file/IFileFormat.h"
#include "parsers/MeterParser.h"

class TxtFormat : public IFileFormat {
public:
    TxtFormat();
    MeterList parse(QTextStream& input) override;
    QString serialize(const MeterList& data) override;
private:
    QString formatMeter(const AbstractMeter* meter);
    MeterParser parser;
};
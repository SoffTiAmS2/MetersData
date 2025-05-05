// include/file/CsvFormat.h
#pragma once
#include "file/IFileFormat.h"
#include "parsers/MeterParser.h"

class CsvFormat : public IFileFormat {
public:
    CsvFormat();
    MeterList parse(QTextStream& input) override;
    QString serialize(const MeterList& data) override;
private:
    QString formatMeter(const AbstractMeter* meter);
    MeterParser parser;
};
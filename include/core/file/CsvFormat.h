// include/file/CsvFormat.h
#pragma once
#include "core/file/IFileFormat.h"
#include "core/model/MeterList.h"
#include "core/model/AbstractMeter.h"
#include "core/parser/MeterParser.h"

class CsvFormat : public IFileFormat {
public:
    CsvFormat();
    MeterList parse(QTextStream& input) override;
    QString serialize(const MeterList& data) override;
private:
    QString formatMeter(const AbstractMeter* meter);
    MeterParser parser;
};
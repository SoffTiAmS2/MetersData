#pragma once

#include "core/file/IFileFormat.h"
#include "core/parser/IMeterParser.h"

class TxtFormat : public IFileFormat {
public:
    TxtFormat();
    void parse(QIODevice& input, MeterList* data) override;
    void serializeTo(QIODevice& output, const MeterList& data) override;

private:
    QString formatMeter(const AbstractMeter* meter);
    
private:
    std::unique_ptr<IMeterParser> parser;
};
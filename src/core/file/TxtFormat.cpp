// src/file/TxtFormat.cpp
#include "core/file/TxtFormat.h"
#include "core/model/MeterList.h"
#include "core/parsUtils/StringSplitter.h"
#include "core/parser/StringMeterParser.h"
#include <QTextStream>
#include <QString>

TxtFormat::TxtFormat()
    : parser(std::make_unique<StringMeterParser>(std::make_unique<StringSplitter>())) {}

    
void TxtFormat::parse(QIODevice& input, MeterList& data) {
    QTextStream in(&input);
    while (!in.atEnd()) {
        QString line = in.readLine();
        data.addMeter(parser->parse(line.toUtf8().toStdString()));
    }
}

void TxtFormat::serializeTo(QIODevice& output, const MeterList& data) {
    QTextStream out(&output);
    for (const auto& meter : data.getMeters()) {
        out << formatMeter(meter.get());
    }
}

QString TxtFormat::formatMeter(const AbstractMeter* meter){
    return QString::fromStdString(meter->toString());
}
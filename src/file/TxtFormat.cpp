// src/file/TxtFormat.cpp
#include "file/TxtFormat.h"
#include "meters/AbstractMeter.h"
#include "parsUtils/StringSplitter.h"
#include <QTextStream>
#include <QString>

TxtFormat::TxtFormat()
    : parser(std::make_unique<StringSplitter>()) {}

MeterList TxtFormat::parse(QTextStream& input) {
    MeterList meters;
    while (!input.atEnd()) {
        QString line = input.readLine();
        try {
            auto meter = parser.parse(line.toStdString());
            meters.addMeter(std::move(meter));
        } catch (const std::exception& e) {
            throw;
        }
    }

    return meters;
}

QString TxtFormat::formatMeter(const AbstractMeter* meter){
    return QString::fromStdString(meter->toString());
}


QString TxtFormat::serialize(const MeterList& data) {
    QString result;
    for (const auto& meter : data.getMeters()) {
        result += formatMeter(meter.get()) + "\n";
    }
    return result;
}
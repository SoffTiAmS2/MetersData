// src/file/CsvFormat.cpp
#include "file/CsvFormat.h"
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <string>
#include "parsUtils/CsvSplitter.h"

CsvFormat::CsvFormat()
    : parser(std::make_unique<CsvSplitter>()) {}

MeterList CsvFormat::parse(QTextStream& input) {
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

QString CsvFormat::formatMeter(const AbstractMeter* meter) {

    std::string teckod = meter->toString();
    std::replace(teckod.begin(), teckod.end(), ' ', ',');

    return QString::fromStdString(teckod);
}

QString CsvFormat::serialize(const MeterList& data) {
    QString result;
    for (const auto& meter : data.getMeters()) {
        result += formatMeter(meter.get()) + "\n";
    }
    return result;
}
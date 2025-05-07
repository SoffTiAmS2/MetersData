// src/file/CsvFormat.cpp
#include "core/file/CsvFormat.h"
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <string>
#include "core/parsUtils/CsvSplitter.h"
#include "core/parser/StringMeterParser.h"

CsvFormat::CsvFormat() : 
    parser (
        std::make_unique<StringMeterParser>(
        std::make_unique<CsvSplitter>()
    )
) {}

void CsvFormat::parse(QIODevice& input, MeterList* data) {

    QTextStream in(&input);

    while (!in.atEnd()) {
    
        QString line = in.readLine();
    
        data->addMeter(parser->parse(line.toUtf8().toStdString()));
    }
}

void CsvFormat::serializeTo(QIODevice& output, const MeterList& data) {

    QTextStream out(&output);

    // out << "Type;Data;Value;Param\n";

    for (const auto& meter : data.getMeters()) {

        out << formatMeter(meter.get()) << '\n';
    }
}

QString CsvFormat::formatMeter(const AbstractMeter* meter) {

    std::string teckod = meter->toString();

    std::replace(teckod.begin(), teckod.end(), ' ', ';');

    return QString::fromStdString(teckod);
}

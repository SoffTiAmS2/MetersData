// src/file/TxtFormat.cpp
#include "core/file/TxtFormat.h"
#include "core/model/MeterList.h"
#include "core/spliter/StringSplitter.h"
#include "core/parser/StringMeterParser.h"
#include "utils/Logger.h"
#include <QTextStream>
#include <QString>
#include <string>

TxtFormat::TxtFormat() : 
    parser(std::make_unique<StringMeterParser> (
        std::make_unique<StringSplitter>()
    )
) {}

    
void TxtFormat::parse(QIODevice& input, MeterList* data) {

    QTextStream in(&input);
    
    int numberLine = 0;

    while (!in.atEnd()) {
    
        QString line = in.readLine();
        numberLine++;
        try{
            data->addMeter(parser->parse(line.toUtf8().toStdString()));
        } catch(const std::exception& e){
            std::string message = std::to_string(numberLine) + " " + e.what();
            Logger::instance().log(message);
            continue;
        }
    }
}

void TxtFormat::serializeTo(QIODevice& output, const MeterList& data) {
    
    QTextStream out(&output);

    for (const auto& meter : data.getMeters()) {
        out << formatMeter(meter.get())  <<  '\n';
    }
}

QString TxtFormat::formatMeter(const AbstractMeter* meter){
    return QString::fromStdString(meter->toString());
}
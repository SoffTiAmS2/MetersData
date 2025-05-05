// src/file/FileHandler.cpp
#include "file/FileHandler.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>  // ← добавлен
#include <memory>
#include "file/TxtFormat.h"
#include "file/CsvFormat.h"

MeterList FileHandler::loadFromFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для чтения: " + path.toStdString());
    }

    QTextStream stream(&file);
    
    std::unique_ptr<IFileFormat> fileUtils = detectFormat(path);
    
    MeterList meters = fileUtils->parse(stream);
    
    file.close();
    return meters;
}

void FileHandler::saveToFile(const QString& path, const MeterList& data) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + path.toStdString());
    }

    QTextStream stream(&file);

    for (const auto& meter : data.getMeters()) {
        stream << meter->toString().c_str() << "\n";
    }

    file.close();
}


std::unique_ptr<IFileFormat> FileHandler::detectFormat(const QString& path) {
    if (path.endsWith(".csv", Qt::CaseInsensitive))
        return std::make_unique<CsvFormat>();
    else if (path.endsWith(".txt", Qt::CaseInsensitive))
        return std::make_unique<TxtFormat>();

    throw std::runtime_error("Неподдерживаемый формат файла");
}
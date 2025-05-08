// src/core/file/FileHandler.cpp
#include "core/file/FileHandler.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>
#include <memory>
#include "core/file/TxtFormat.h"
#include "core/file/CsvFormat.h"

void FileHandler::save(const QString& path, const MeterList& data) const {
    auto formatter = detectFormat(path);

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + path.toStdString());
    }
    
    formatter->serializeTo(file, data);

    file.close();
}

void FileHandler::load(const QString& path, MeterList* data) const {

    auto formatter = detectFormat(path);

    QFile file(path);


    if (!file.open(QIODevice::ReadOnly)) {

        throw std::runtime_error(
            "Не удалось открыть файл для чтения: " + path.toStdString()
        );
    }

    formatter->parse(file, data);
    file.close();
}

std::unique_ptr<IFileFormat> FileHandler::detectFormat(const QString& path) const {

    if (path.endsWith(".csv", Qt::CaseInsensitive))
        return std::make_unique<CsvFormat>();
    
    else if (path.endsWith(".txt", Qt::CaseInsensitive))
        return std::make_unique<TxtFormat>();

    throw std::runtime_error("Неподдерживаемый формат файла");
}
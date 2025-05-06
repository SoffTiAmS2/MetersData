// include/file/FileHandler.h
#pragma once
#include "IFileFormat.h"
#include <QString>


class FileHandler {
public:
    MeterList loadFromFile(const QString& path);
    void saveToFile(const QString& path, const MeterList& data);

private:
    std::unique_ptr<IFileFormat> detectFormat(const QString& path);
};
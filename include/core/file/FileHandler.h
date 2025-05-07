// include/core/file/FileHandler.h
#pragma once
#include "IFileFormat.h"
#include <QString>


class FileHandler {
public:
    void load(const QString& path, MeterList& data) const;
    void save(const QString& path, const MeterList& data) const;

private:
    std::unique_ptr<IFileFormat> detectFormat(const QString& path) const;
};
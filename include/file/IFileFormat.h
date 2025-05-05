// include/file/FileFormat.h
#pragma once
#include "meters/MeterList.h"
#include <QTextStream>

class IFileFormat {
public:
    virtual ~IFileFormat() = default;
    virtual MeterList parse(QTextStream& input) = 0;
    virtual QString serialize(const MeterList& data) = 0;
};
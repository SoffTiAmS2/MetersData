// include/file/FileFormat.h
#pragma once
#include "core/model/MeterList.h"
#include <QTextStream>

class IFileFormat {
public:
    virtual ~IFileFormat() = default;
    virtual MeterList parse(QTextStream& input) = 0;
    virtual QString serialize(const MeterList& data) = 0;
};